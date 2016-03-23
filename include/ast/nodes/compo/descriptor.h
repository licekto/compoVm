#pragma once

#include <memory>
#include <algorithm>

#include "ast/nodes/node.h"
#include "ast/nodes/compo/port.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/compo/signaturesPort.h"
#include "ast/nodes/compo/serviceSignature.h"
#include "ast/nodes/compo/abstractReqProv.h"
#include "ast/nodes/compo/provision.h"
#include "ast/nodes/compo/requirement.h"
#include "ast/nodes/compo/architecture.h"
#include "ast/nodes/compo/abstractDescriptorInterface.h"

namespace ast {

	namespace nodes {

		namespace compo {

			/**
			 * \class CDescriptor
			 * \brief Class for Compo descriptor representation.
			 */
			class CDescriptor : public CAbstractDescriptorInterface, public std::enable_shared_from_this<CDescriptor> {
			  private:
				std::shared_ptr<compo::CProvision> m_internalProvision;

				std::shared_ptr<compo::CProvision> m_externalProvision;

				std::shared_ptr<compo::CRequirement> m_internalRequirement;

				std::shared_ptr<compo::CRequirement> m_externalRequirement;

				std::shared_ptr<compo::CArchitecture> m_architecture;

				/**< Vector of descriptor body nodes */
				std::vector<std::shared_ptr<compo::CService>> m_services;

				std::vector<std::shared_ptr<compo::CConstraint>> m_constraints;

				/**< Every descriptor contains default port */
				std::shared_ptr<compo::CPort> m_defaultPort;

				/**< Every descriptor contains self port */
				std::shared_ptr<compo::CPort> m_selfPort;

				bool findPortIn(std::shared_ptr<compo::CAbstractReqProv> reqProv, const std::string& name) const;
			  public:
				/**
				* Parametric constructor with default values
				* @param name: name of descriptor
				* @param extends: name of parent descriptor
				* @param body: vector of body nodes
				*/
				CDescriptor(std::shared_ptr<procedural::CSymbol> name = nullptr,
				            std::shared_ptr<procedural::CSymbol> extends = nullptr,
				            std::shared_ptr<compo::CProvision> inProv = nullptr,
				            std::shared_ptr<compo::CProvision> exProv = nullptr,
				            std::shared_ptr<compo::CRequirement> inReq = nullptr,
				            std::shared_ptr<compo::CRequirement> exReq = nullptr,
				            std::shared_ptr<compo::CArchitecture> arch = nullptr,
				            const std::vector<std::shared_ptr<compo::CService>>& services = std::vector<std::shared_ptr<compo::CService>>(0),
				            const std::vector<std::shared_ptr<compo::CConstraint>>& constraints = std::vector<std::shared_ptr<compo::CConstraint>>(0));

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Body vector size getter
				 * @return number of elements in body
				 */
				size_t getServicesSize() const;

				size_t getConstraintsSize() const;

				/**
				* Body getter
				* @return Constant pointer to body vector
				*/
				std::shared_ptr<compo::CService> getServiceAt(int index) const;

				std::shared_ptr<compo::CConstraint> getConstraintAt(int index) const;

				std::shared_ptr<compo::CProvision> getInProvision() const;

				std::shared_ptr<compo::CProvision> getExProvision() const;

				std::shared_ptr<compo::CRequirement> getInRequirement() const;

				std::shared_ptr<compo::CRequirement> getExRequirement() const;

				std::shared_ptr<compo::CArchitecture> getArchitecture() const;

				/**
				* Default port getter
				                * @return Constant pointer to port
				                */
				std::shared_ptr<compo::CPort> getDefaultPort() const;

				/**
				* Self port getter
				                * @return Constant pointer to port
				                */
				std::shared_ptr<compo::CPort> getSelfPort() const;

				bool portFound(const std::string& name) const;

				bool inProvidedPortFound(const std::string& name) const;

				bool exProvidedPortFound(const std::string& name) const;

				bool inRequiredPortFound(const std::string& name) const;

				bool exRequiredPortFound(const std::string& name) const;

				std::shared_ptr<compo::CService> getServiceByName(const std::string& name) const;
			};

		}

	}

}