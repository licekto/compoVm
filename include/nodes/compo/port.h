#pragma once

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
			procedural::CSymbol                  * m_name;         /**< Name symbol of port */
			bool                            m_atomic;       /**< Is atomic? */

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CPort          (procedural::CSymbol *name = nullptr, bool atomic = false);

			/**
			* Copy constructor
			* @param other: reference to another object of same type
			*/
			CPort          (const CPort& other);

			/**
			* Move constructor
			* @param other: rvalue-reference to another object of same type
			*/
			CPort          (CPort&& other) noexcept;

			/**
			* Copy assignment operator
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CPort&                     operator=           (const CPort& other);

			/**
			* Move assignment operator
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CPort&                     operator=           (CPort&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual CNode *                    clone                   () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CPort         ();

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& os) const;

			/**
			* Name getter
			* @return Name of port
			*/
			std::string                     getName             () const;

			/**
			* Atomic getter
			* @return is atomic?
			*/
			bool                            getAtomic           () const;
		};

	}

}