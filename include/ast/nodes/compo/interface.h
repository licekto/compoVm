#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/compo/serviceSignature.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/compo/abstractDescriptorInterface.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CInterface
			 * \brief Class for interface representation.
			 */
			class CInterface : public CAbstractDescriptorInterface, public std::enable_shared_from_this<CInterface> {
			  private:

				/**< List of signatures */
				std::vector<std::shared_ptr<compo::CServiceSignature>> m_signaturesList;

			  public:
				/**
				* Parametric constructor with default value
				* @param name: Name of interface
				* @param extends: Name of super-interface
				                * @param list: List of service signatures
				*/
				CInterface(std::shared_ptr<procedural::CSymbol> name = nullptr,
				           std::shared_ptr<procedural::CSymbol> extends = nullptr,
				           std::vector<std::shared_ptr<compo::CServiceSignature>> list = std::vector<std::shared_ptr<compo::CServiceSignature>>(0));

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Signatures size getter
				 * @return size_t
				 */
				size_t getSignaturesSize() const;

				/**
				 * Signatures getter
				 * @param index
				 * @return shared_ptr to CServiceSignature
				 */
				std::shared_ptr<compo::CServiceSignature> getSignatureAt(unsigned int index) const;
			};

		}

	}

}