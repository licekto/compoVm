#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/symbol.h"

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
			/**< Name symbol of port */
			std::shared_ptr<nodes::procedural::CSymbol> m_name;

			/**< Is atomic? */
			bool m_atomic;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CPort(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr, bool atomic = false);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			* Name getter
			* @return Name of port
			*/
			std::string getName() const;

			/**
			* Atomic getter
			* @return is atomic?
			*/
			bool getAtomic() const;
		};

	}

}