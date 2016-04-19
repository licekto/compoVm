#pragma once

#include <memory>

#include "ast/nodes/node.h"
#include "ast/nodes/procedural/symbol.h"
#include "types.h"

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
				types::portType m_portType;

				/**< Name symbol of port */
				std::shared_ptr<nodes::procedural::CSymbol> m_name;

				/**< Is atomic? */
				bool m_atomicity;

				/**< Kind name symbol of port */
				std::shared_ptr<nodes::procedural::CSymbol> m_kindOf;

				/**< Is atomic? */
				bool m_collectivity;

				/**< Type of visibility */
				types::visibilityType m_visibilityType;

				types::roleType m_role;

			  public:
				/**
				* Parametric constructor with default value
				* @param name: Name of port
				* @param atomic: Is atomic?
				*/
				CPort(types::portType type = types::portType::UNIVERSAL,
				      std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
				      bool atomicity = false,
				      bool collectivity = false,
				      types::visibilityType visibility = types::visibilityType::EXTERNAL,
				      types::roleType role = types::roleType::PROVIDES);

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
                                * @return types::portType
                                */
				types::portType getPortType() const;

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
				bool isCollection() const;

				void setVisibility(types::visibilityType visibility);

				types::visibilityType getVisibility() const;

				void setRole(types::roleType role);

				types::roleType getRole() const;
			};

		}

	}

}