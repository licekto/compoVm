#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/compo/bind.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CArchitecture
		 * \brief Class for Compo architecture representation.
		 */
		class CArchitecture : public CNode {
                private:
                    /**< Vector of architecture body nodes */
                    std::vector<std::shared_ptr<nodes::compo::CBind>> m_architectureBody;
                    
		  public:
			/**
			* Default constructor
			*/
			CArchitecture(const std::vector<std::shared_ptr<nodes::compo::CBind>>& architectureBody = std::vector<std::shared_ptr<nodes::compo::CBind>>(0));

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
                        
                        /**
                         * Archi
                         * @return 
                         */
                        std::shared_ptr<nodes::compo::CBind> getBodyNodeAt(unsigned int index) const;
		};

	}

}