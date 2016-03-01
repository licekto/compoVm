#pragma once

#include "nodes/node.h"
#include "nodes/procedural/symbol.h"


/**
* \struct TBlock
* \brief Block structure to hold temporaries and statements inside of compound_block
*/
typedef struct TBlock {
	std::vector<std::shared_ptr<nodes::procedural::CSymbol>>    temporaries;    /**< Temporaries vector */
	std::vector<std::shared_ptr<nodes::CNode>>                  statements;     /**< Statements vector */

	void                        clear();
} TBLOCK;