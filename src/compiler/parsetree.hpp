#pragma once

enum node_type
{
	NODE_INCLUDE,

};

union sval_u
{
	sval_u* node;
	uint8_t type;
};

class parsetree
{
	static sval_u* alloc_node(size_t size);
	static sval_u node1_(std::int32_t val1);
	static sval_u node2_(sval_u val1, sval_u val2);
	static sval_u node0(uint8_t type);
	static sval_u node1(uint8_t type, sval_u val1);
	static sval_u node2(uint8_t type, sval_u val1, sval_u val2);
	static sval_u node3(uint8_t type, sval_u val1, sval_u val2, sval_u val3);
	static sval_u node4(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4);
	static sval_u node5(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5);
	static sval_u node6(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6);
	static sval_u node7(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7);
	static sval_u node8(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7, sval_u val8);
	static sval_u linked_list(sval_u val);
	static sval_u prepend_node(sval_u val1, sval_u val2);
	static sval_u append_node(sval_u val1, sval_u val2);
};
