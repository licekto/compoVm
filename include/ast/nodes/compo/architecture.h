#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/compo/bind.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		/**
		 * \class CArchitecture
		 * \brief Class for Compo architecture representation.
		 */
		class CArchitecture : public CNode, public std::enable_shared_from_this<CArchitecture> {
		  private:
			/**< Vector of architecture body nodes */
			std::vector<std::shared_ptr<compo::CBind>> m_architectureBody;

		  public:
			/**
			* Default constructor
			*/
			CArchitecture(const std::vector<std::shared_ptr<compo::CBind>>& architectureBody = std::vector<std::shared_ptr<compo::CBind>>(0));

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

			/**
			 * Body size getter
			 * @return size_t
			 */
			size_t getBodySize() const;

			/**
			 * Architecture nodes getter
			 * @return shared pointer to CBind
			 */
			std::shared_ptr<compo::CBind> getBodyNodeAt(unsigned int index) const;
		};

	}
        
    }

}