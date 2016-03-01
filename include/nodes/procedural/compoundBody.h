#pragma once

#include <memory>
#include "nodes/node.h"
#include "symbol.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CCompoundBody
		 * \brief Class for representation body of compound statement
		         *
		         * Compound statement contains temporaries (| var1 var2 | syntax) and standard procedural statements. Therefore separate class was made to simplify body handling.
		 */
		class CCompoundBody : public CNode {
		  private:
			std::vector<std::shared_ptr<nodes::procedural::CSymbol>>  m_temporaries;              /**< Temporaries vector */
			std::vector<std::shared_ptr<nodes::CNode>>              m_body;                     /**< Body nodes vector */

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			*/
			CCompoundBody                ( const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& temporaries = std::vector<std::shared_ptr<nodes::procedural::CSymbol>>(0),
			                               const std::vector<std::shared_ptr<nodes::CNode>>& body = std::vector<std::shared_ptr<nodes::CNode>>(0));

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& os) const;

			/**
			* Body getter
			* @return Constant pointer to body vector
			*/
			std::shared_ptr<nodes::CNode>                    getBodyNodeAt       (int index) const;

			/**
			* Body getter
					* @return Constant pointer to body vector
					*/
			std::shared_ptr<nodes::procedural::CSymbol>                    getTemporaryAt       (int index) const;
		};

	}

}