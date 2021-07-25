#pragma once
#ifndef HAVE_BLOCK_ARRAY_CONTAINER_H
#define HAVE_BLOCK_ARRAY_CONTAINER_H

#include <exception>
#include <string>
#include <vector>
#include <gsl/span>

#include "PalettedBlockArray.h"

#define MACRO_PER_BITS_PER_BLOCK \
	BPB_MACRO(1) \
	BPB_MACRO(2) \
	BPB_MACRO(3) \
	BPB_MACRO(4) \
	BPB_MACRO(5) \
	BPB_MACRO(6) \
	BPB_MACRO(8) \
	BPB_MACRO(16)

template<typename Block>
class BlockArrayContainer {
private:
	typedef IPalettedBlockArray<Block> BlockArray;

	static BlockArray *blockArrayFromData(uint8_t bitsPerBlock, gsl::span<uint8_t> &wordArray, std::vector<Block> &paletteEntries) {
		switch (bitsPerBlock) {
#define BPB_MACRO(i) case i: return new PalettedBlockArray<i, Block>(wordArray, paletteEntries);
			MACRO_PER_BITS_PER_BLOCK
#undef BPB_MACRO
		default:
			throw std::runtime_error("invalid bits-per-block: " + std::to_string(bitsPerBlock));
		}
	}

	static BlockArray *blockArrayFromCapacity(unsigned short capacity) {
#define BPB_MACRO(i) \
		if (capacity <= PalettedBlockArray<i, Block>::MAX_PALETTE_SIZE) { \
			return new PalettedBlockArray<i, Block>; \
		}

		MACRO_PER_BITS_PER_BLOCK
#undef BPB_MACRO

		throw std::invalid_argument("invalid capacity specified: " + std::to_string(capacity));
	}

	BlockArray *blockArray = nullptr;

public:
	static unsigned int getExpectedPayloadSize(uint8_t bitsPerBlock) {
		switch (bitsPerBlock) {
#define BPB_MACRO(i) case i: return PalettedBlockArray<i, Block>::PAYLOAD_SIZE;
			MACRO_PER_BITS_PER_BLOCK
#undef BPB_MACRO
		default:
			throw std::invalid_argument("invalid bits-per-block: " + std::to_string(bitsPerBlock));
		}
	}

	BlockArrayContainer(Block block) {
		blockArray = new PalettedBlockArray<1, Block>(block);
	}

	BlockArrayContainer(unsigned short capacity) {
		blockArray = blockArrayFromCapacity(capacity);
	}

	BlockArrayContainer(uint8_t bitsPerBlock, gsl::span<uint8_t> &wordArray, std::vector<Block> &paletteEntries) {
		blockArray = blockArrayFromData(bitsPerBlock, wordArray, paletteEntries);
	}

	BlockArrayContainer(const BlockArrayContainer &other) {
		blockArray = other.blockArray->clone();
	}

	BlockArrayContainer& operator=(const BlockArrayContainer &other) {
		if (&other != this) {
			delete blockArray;
			blockArray = other.blockArray->clone();
		}
		return *this;
	}

	~BlockArrayContainer() {
		delete blockArray;
	}

	// A godawful hack to avoid thousands of virtual calls during conversion and other things.
	template<typename ReturnType, typename Visited>
	ReturnType specializeForArraySize(Visited& v) {
#define BPB_MACRO(size) \
		if (auto casted = dynamic_cast<PalettedBlockArray<size, Block>*>(blockArray)){ \
			return v.template visit<size>(*casted); \
		}

		MACRO_PER_BITS_PER_BLOCK
#undef BPB_MACRO

		v.visit(*blockArray);
	}

	const gsl::span<const char> getWordArray() const {
		return blockArray->getWordArray();
	}

	const gsl::span<const Block> getPalette() const {
		return blockArray->getPalette();
	}

	unsigned short getMaxPaletteSize() const {
		return blockArray->getMaxPaletteSize();
	}

	uint8_t getBitsPerBlock() const {
		return blockArray->getBitsPerBlock();
	}

	Block get(unsigned char x, unsigned char y, unsigned char z) const {
		return blockArray->get(x, y, z);
	}

	void set(unsigned char x, unsigned char y, unsigned char z, Block val) {
		if (!blockArray->set(x, y, z, val)) {
			unsigned short count = blockArray->getPaletteSize();
			if (count < BlockArray::ARRAY_CAPACITY) {
				//reached max capacity and less than ARRAY_CAPACITY unique blocks in array
				//this also automatically handles GC on chunks when there are unused palette entries in an array

				BlockArray *newArray = blockArrayFromCapacity(count + 1);

				newArray->fastUpsize(*blockArray);
				newArray->set(x, y, z, val);
				delete blockArray;
				blockArray = newArray;
			} else if (blockArray->needsGarbageCollection()) {
				//full palette but GC possible, run GC and try a second time
				collectGarbage(false, 1);
				set(x, y, z, val);
			} else {
				//full palette and GC not possible, force overwrite of existing blockstate
				//this means there are no unused entries and this block isn't already in the palette, so GC is impossible
				blockArray->replace(blockArray->getPaletteOffset(x, y, z), val);
				blockArray->setGarbageCollected();
			}
		}
	}

	void replace(unsigned short offset, Block val) {
		blockArray->replace(offset, val);
	}

	void replaceAll(Block oldVal, Block newVal) {
		blockArray->replaceAll(oldVal, newVal);
	}

	// Repacks the block array to the smallest format possible with the number of unique blocks found
	void collectGarbage(bool forceCollect, unsigned short reserved = 0) {
		if (forceCollect || blockArray->needsGarbageCollection()) {
			auto unique = blockArray->countUniqueBlocks();

			if (unique != blockArray->getPaletteSize()) {
				BlockArray *newArray = blockArrayFromCapacity(unique + reserved);
				assert(newArray != nullptr);
				newArray->convertFrom(*blockArray);
				delete blockArray;
				blockArray = newArray;
			}
			blockArray->setGarbageCollected();
		}
	}

	// Bypass GC and flag the array as garbage-collected. Useful in bulk writes such as external conversion.
	void setGarbageCollected() {
		blockArray->setGarbageCollected();
	}
};

#endif
