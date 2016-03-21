#pragma once

#include <memory>

#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/types/portType.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CPort
			 * \brief Class for port and inherited injected port nodes.
			 *
			 * Class for port and inherited injected port nodes. Class inherits virtually from nodes::CNode prevent diamond problem.
			 * This class was designed because of the similar structure of port a injected port nodes thus to prevent code repetition.
			 */
			class CPort : public virtual CNode {
			  protected:
				/**< Type of port */
				nodes::types::portType m_portType;

				/**< Name symbol of port */
				std::shared_ptr<nodes::procedural::CSymbol> m_name;

				/**< Is atomic? */
				bool m_atomicity;

				/**< Kind name symbol of port */
				std::shared_ptr<nodes::procedural::CSymbol> m_kindOf;

				/**< Is atomic? */
				bool m_collectivity;

			  public:
				/**
				* Parametric constructor with default value
				* @param name: Name of port
				* @param atomic: Is atomic?
				*/
				CPort(nodes::types::portType type = nodes::types::portType::UNIVERSAL,
				      std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
				      bool atomicity = false,
				      bool collectivity = false);

				/**
				            * Accept method for visitor acceptation.
				            * @param visitor: Pointer to abstract visitor.
				            */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;

				/**
				* Name getter
				* @return Name of port
				*/
				std::shared_ptr<nodes::procedural::CSymbol> getNameSymbol() const;

				/**
				* Atomicity getter
				* @return is atomic?
				*/
				bool getAtomicity() const;

				/**
				* Port type getter
						* @return nodes::types::portType
						*/
				nodes::types::portType getPortType() const;

				/**
				 * Kind of name setter
				 * @param kindOf
				 */
				void setKindOf(std::shared_ptr<nodes::procedural::CSymbol> kindOf);

				/**
				 * Kind of name getter
				 * @return symbol of kindOf
				 */
				std::shared_ptr<nodes::procedural::CSymbol> getKindOf() const;

				/**
				* Collectivity getter
						* @return is collective?
						*/
				bool getCollectivity() const;
			};

		}

	}

}