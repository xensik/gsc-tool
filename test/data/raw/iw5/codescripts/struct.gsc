InitStructs()
{
	level.struct = [];
}

CreateStruct()
{
	struct = spawnstruct();
	level.struct[level.struct.size] = struct;
	return struct;
}
