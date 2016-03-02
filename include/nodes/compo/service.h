#pragma once

#include <memory>
#include "nodes/compo/abstractServConstr.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CService
		 * \brief Class for Compo service node representation.
		 */
		class CService : public CAbstractServConstr {
		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name symbol of service
			* @param params: Vector of parameters
			* @param body: Vector of body nodes
			* @param temporaries: Vector of temporaries
			*/
			CService(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
                                            const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params = std::vector<std::shared_ptr<nodes::procedural::CSymbol>>(0),
                                            std::shared_ptr<nodes::procedural::CCompoundBody> body = nullptr);
                        /**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
		};

	}

}