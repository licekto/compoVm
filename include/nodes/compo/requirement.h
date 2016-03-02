#pragma once

#include <memory>
#include "nodes/compo/abstractReqProv.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CRequirement
		 * \brief Class for Compo requirement node representation.
		 */
		class CRequirement : public CAbstractReqProv {
		  public:
			/**
			* Parametric constructor with default value
			* @param type: Type of visibility
			* @param ports: Vector of ports
			*/
			CRequirement(types::visibilityType type = types::visibilityType::EXTERNAL,
			             const std::vector<std::shared_ptr<nodes::compo::CPort>>& ports = std::vector<std::shared_ptr<nodes::compo::CPort>>(0),
                                     bool universality = false);

			/**
			* Virtual print function to call from operator <<
                        * @param os: output stream
                        * @see operator <<()
                        */
			virtual void print(std::ostream& os) const;
		};

	}

}