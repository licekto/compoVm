#pragma once

#include <memory>
#include "nodes/compo/serviceSignature.h"
#include "nodes/procedural/symbol.h"

namespace nodes {

	namespace compo {

		/**
		 * \class CSignaturesPort
		 * \brief Class for port with signatures list.
		 */
		class CSignaturesPort : public CPort {
		  protected:
			/**< List of signatures */
			std::vector<std::shared_ptr<nodes::compo::CServiceSignature>> m_signaturesList;

		  public:
			/**
			* Parametric constructor with default value
			* @param name: Name of port
			* @param atomic: Is atomic?
			*/
			CSignaturesPort(std::shared_ptr<nodes::procedural::CSymbol> name = nullptr,
			                bool atomicity = false,
			                std::vector<std::shared_ptr<nodes::compo::CServiceSignature>> list = std::vector<std::shared_ptr<nodes::compo::CServiceSignature>>(0));

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

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
			std::shared_ptr<nodes::compo::CServiceSignature> getSignatureAt(unsigned int index) const;
		};

	}

}