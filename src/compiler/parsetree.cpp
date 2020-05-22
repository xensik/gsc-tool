#include "stdinc.hpp"
#include "parsetree.hpp"

sval_u node_pool[0x1000]; // or malloc?

sval_u* parsetree::alloc_node(size_t size)
{
	// return (sval_u*)std::malloc(sizeof(sval_u) * size);

	return 0;
}

sval_u parsetree::node1_(std::int32_t val1)
{
	return *(sval_u*)&val1;
}

sval_u parsetree::node2_(sval_u val1, sval_u val2)
{
	sval_u result;

	result.node = parsetree::alloc_node(2);
	result.node->node = val1.node;
	result.node[1].node = val2.node;

	return result;
}

sval_u parsetree::node0(uint8_t type)
{
	sval_u result;
	result.node = parsetree::alloc_node(1);

	result.node->type = type;

	return result;
}

sval_u parsetree::node1(uint8_t type, sval_u val1)
{
	sval_u result;
	result.node = parsetree::alloc_node(2);

	result.node->type = type;
	result.node[1].node = val1.node;

	return result;
}

sval_u parsetree::node2(uint8_t type, sval_u val1, sval_u val2)
{
	sval_u result;
	result.node = parsetree::alloc_node(3);

	result.node->type = type;
	result.node[1].node = val1.node;
	result.node[2].node = val2.node;

	return result;
}

sval_u parsetree::node3(uint8_t type, sval_u val1, sval_u val2, sval_u val3)
{
	sval_u result;
	result.node = parsetree::alloc_node(4);

	result.node->type = type;
	result.node[1].node = val1.node;
	result.node[2].node = val2.node;
	result.node[3].node = val3.node;

	return result;
}
sval_u parsetree::node4(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4)
{
	sval_u result;
	result.node = parsetree::alloc_node(5);

	result.node->type = type;
	result.node[1].node = val1.node;
	result.node[2].node = val2.node;
	result.node[3].node = val3.node;
	result.node[4].node = val4.node;

	return result;
}

sval_u parsetree::node5(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5)
{
	sval_u result;
	result.node = parsetree::alloc_node(6);

	result.node->type = type;
	result.node[1].node = val1.node;
	result.node[2].node = val2.node;
	result.node[3].node = val3.node;
	result.node[4].node = val4.node;
	result.node[5].node = val5.node;

	return result;
}

sval_u parsetree::node6(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6)
{
	sval_u result;
	result.node = parsetree::alloc_node(7);

	result.node->type = type;
	result.node[1].node = val1.node;
	result.node[2].node = val2.node;
	result.node[3].node = val3.node;
	result.node[4].node = val4.node;
	result.node[5].node = val5.node;
	result.node[6].node = val6.node;

	return result;
}

sval_u parsetree::node7(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7)
{
	sval_u result;
	result.node = parsetree::alloc_node(8);

	result.node->type = type;
	result.node[1].node = val1.node;
	result.node[2].node = val2.node;
	result.node[3].node = val3.node;
	result.node[4].node = val4.node;
	result.node[5].node = val5.node;
	result.node[6].node = val6.node;
	result.node[7].node = val7.node;

	return result;
}

sval_u parsetree::node8(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7, sval_u val8)
{
	sval_u result;
	result.node = parsetree::alloc_node(9);

	result.node->type = type;
	result.node[1].node = val1.node;
	result.node[2].node = val2.node;
	result.node[3].node = val3.node;
	result.node[4].node = val4.node;
	result.node[5].node = val5.node;
	result.node[6].node = val6.node;
	result.node[7].node = val7.node;
	result.node[8].node = val8.node;

	return result;
}

sval_u parsetree::linked_list(sval_u val)
{
	sval_u* node;
	sval_u result;

	node = alloc_node(2);
	*node = val;
	node[1].node = 0;

	result.node = alloc_node(2);
	result.node->node = node;
	result.node[1].node = node;

	return result;
}

sval_u parsetree::prepend_node(sval_u val1, sval_u val2)
{
	sval_u* v3;

	v3 = alloc_node(2);
	*v3 = val1;
	v3[1] = *val2.node;
	val2.node->node = v3;

	return val2;
}

sval_u parsetree::append_node(sval_u val1, sval_u val2)
{
	sval_u* v3;

	v3 = alloc_node(2);
	*v3 = val2;
	v3[1].node = 0;
	val1.node[1].node[1].node = v3;
	val1.node[1].node = v3;

	return val1;
}
