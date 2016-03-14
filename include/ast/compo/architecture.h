#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/compo/bind.h"

namespace ast {

	namespace compo {

		/**
		 * \class CArchitecture
		 * \brief Class for Compo architecture representation.
		 */
		class CArchitecture : public CNode {
		  private:
			/**< Vector of architecture body nodes */
			std::vector<std::shared_ptr<ast::compo::CBind>> m_architectureBody;

		  public:
			/**
			* Default constructor
			*/
			CArchitecture(const std::vector<std::shared_ptr<ast::compo::CBind>>& architectureBody = std::vector<std::shared_ptr<ast::compo::CBind>>(0));

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			 * Body size getter
			 * @return size_t
			 */
			size_t getBodySize() const;

			/**
			 * Architecture nodes getter
			 * @return shared pointer to CBind
			 */
			std::shared_ptr<ast::compo::CBind> getBodyNodeAt(unsigned int index) const;
		};

	}

}