/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 614c40369f253f1a9e6238b5a5e5e7c43c3c25e5 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkXZY, 0, 2, pocketmine\\world\\format\\PalettedBlockArray, 0)
	ZEND_ARG_TYPE_INFO(0, idArray, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, metaArray, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkYZX arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkXZY

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkFromLegacyColumn, 0, 3, pocketmine\\world\\format\\PalettedBlockArray, 0)
	ZEND_ARG_TYPE_INFO(0, idArray, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, metaArray, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, yOffset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkFromPaletteXZY, 0, 2, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, palettedBlockArray, pocketmine\\world\\format\\PalettedBlockArray, 0)
	ZEND_ARG_TYPE_INFO(0, protocol, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_pocketmine_world_format_io_SubChunkConverter___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(pocketmine_world_format_io_SubChunkConverter, convertSubChunkXZY);
ZEND_METHOD(pocketmine_world_format_io_SubChunkConverter, convertSubChunkYZX);
ZEND_METHOD(pocketmine_world_format_io_SubChunkConverter, convertSubChunkFromLegacyColumn);
ZEND_METHOD(pocketmine_world_format_io_SubChunkConverter, convertSubChunkFromPaletteXZY);
ZEND_METHOD(pocketmine_world_format_io_SubChunkConverter, __construct);


static const zend_function_entry class_pocketmine_world_format_io_SubChunkConverter_methods[] = {
	ZEND_ME(pocketmine_world_format_io_SubChunkConverter, convertSubChunkXZY, arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkXZY, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(pocketmine_world_format_io_SubChunkConverter, convertSubChunkYZX, arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkYZX, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(pocketmine_world_format_io_SubChunkConverter, convertSubChunkFromLegacyColumn, arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkFromLegacyColumn, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(pocketmine_world_format_io_SubChunkConverter, convertSubChunkFromPaletteXZY, arginfo_class_pocketmine_world_format_io_SubChunkConverter_convertSubChunkFromPaletteXZY, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(pocketmine_world_format_io_SubChunkConverter, __construct, arginfo_class_pocketmine_world_format_io_SubChunkConverter___construct, ZEND_ACC_PRIVATE)
	ZEND_FE_END
};
