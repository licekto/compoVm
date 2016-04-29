#pragma once

#include <memory>
#include "ast/nodes/compo/serviceSignature.h"
#include "ast/nodes/procedural/symbol.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CSignaturesPort
			 * \brief Class for port with signatures list.
			 */
			class CSignaturesPort : public CPort, public std::enable_shared_from_this<CSignaturesPort> {
			  protected:
				/**< List of signatures */
				std::vector<std::shared_ptr<compo::CServiceSignature>> m_signaturesList;

			  public:
				/**
				* Parametric constructor with default value
				                * @param name: Name of port
				                * @param atomicity: is atomic?
				                * @param collectivity: is collection?
				                * @param visibilityType: Visibility type
				                * @param role: Role type
				                * @param list: Signatures list
				*/
				CSignaturesPort(std::shared_ptr<procedural::CSymbol> name = nullptr,
				                bool atomicity = false,
				                bool collectivity = false,
				                types::visibilityType visibility = types::visibilityType::EXTERNAL,
				                types::roleType role = types::roleType::PROVIDES,
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