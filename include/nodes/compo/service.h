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
		  private:
			std::vector<std::shared_ptr<nodes::CNode>>        m_temporaries;      /**< Type of node */
		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name symbol of service
			* @param params: Vector of parameters
			* @param body: Vector of body nodes
			* @param temporaries: Vector of temporaries
			*/
			CService       ( std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			                 const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params = std::vector<std::shared_ptr<nodes::procedural::CSymbol>>(0),
			                 const std::vector<std::shared_ptr<nodes::CNode>>& body = std::vector<std::shared_ptr<nodes::CNode>>(0),
			                 const std::vector<std::shared_ptr<nodes::CNode>>& temporaries = std::vector<std::shared_ptr<nodes::CNode>>(0)  );

			/**
			 * Number of temporaries getter
			 * @return number of temporaries
			 */
			size_t                          getTemporariesSize  () const;
			/**
			 * Temporaries getter
			 * @return constant pointer to temporaries
			 */
			std::shared_ptr<nodes::CNode>                    getTemporaryAt      (int index) const;

			virtual void                            print               (std::ostream& os) const;
		};

	}

}