#pragma once

#include <memory>
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CNamedPort
		 * \brief Class for named port representation.
		 */
		class CCollectionPortLiteral : public CNode {
		  protected:
			/**< Name parameter symbol of port */
			std::shared_ptr<nodes::procedural::CSymbol> m_portName;
                        
                        /**< Index expression */
                        std::shared_ptr<nodes::procedural::CAbstractExpression> m_indexExpression;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CCollectionPortLiteral(std::shared_ptr<nodes::procedural::CSymbol> portName = nullptr,
                                               std::shared_ptr<nodes::procedural::CAbstractExpression> indexExpression = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			 * Signatures getter
			 * @return shared_ptr to CServiceSignature
			 */
			std::shared_ptr<nodes::procedural::CSymbol> getPortName() const;
                        
                        /**
			 * Index expression getter
			 * @return shared_ptr to CAbstractExpression
			 */
                        std::shared_ptr<nodes::procedural::CAbstractExpression> getIndexExpression() const;
		};

	}

}