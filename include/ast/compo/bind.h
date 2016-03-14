#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/procedural/symbol.h"
#include "portAddress.h"

namespace ast {

	namespace compo {

		/**
		 * \class CInjectedPort
		 * \brief Class for Compo injected port representation
		 */
		class CBind : public virtual CNode {
		  protected:
			/**< Name symbol of port 1 */
			std::shared_ptr<ast::compo::CPortAddress> m_portIdentification1;

			/**< Name symbol of port 2 */
			std::shared_ptr<ast::compo::CPortAddress> m_portIdentification2;

			/**
			* Parametric constructor with default values
			* @param name: name of port
			* @param atomic: is atomic
			* @param injectedWith: name of injected port
			*/
			CBind(std::shared_ptr<ast::compo::CPortAddress> portIdentification1 = nullptr,
			      std::shared_ptr<ast::compo::CPortAddress> portIdentification2 = nullptr);

		  public:

                        /**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);
                      
			/**
			 * Port name getter
			 * @return name symbol of port identification.
			 */
			std::shared_ptr<ast::compo::CPortAddress> getPortIdentification1() const;

			/**
			* Port name getter
                        * @return name symbol of port identification.
                        */
			std::shared_ptr<ast::compo::CPortAddress> getPortIdentification2() const;
		};

	}

}