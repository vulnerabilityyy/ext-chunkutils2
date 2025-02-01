<?php

/**
 * @generate-function-entries
 */

namespace pocketmine\world\format\io;

final class SubChunkConverter{

	public static function convertSubChunkXZY(string $idArray, string $metaArray) : \pocketmine\world\format\PalettedBlockArray{}

	public static function convertSubChunkYZX(string $idArray, string $metaArray) : \pocketmine\world\format\PalettedBlockArray{}

	public static function convertSubChunkFromLegacyColumn(string $idArray, string $metaArray, int $yOffset) : \pocketmine\world\format\PalettedBlockArray{}

	public static function convertSubChunkFromPaletteXZY(\pocketmine\world\format\PalettedBlockArray $palette, int $protocol) : string{}

	private function __construct(){}
}
