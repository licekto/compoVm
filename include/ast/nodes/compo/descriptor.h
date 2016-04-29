#pragma once

#include <memory>
#include <algorithm>

#include "logger/logger.h"

#include "ast/nodes/node.h"
#include "ast/nodes/compo/port.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/compo/signaturesPort.h"
#include "ast/nodes/compo/serviceSignature.h"
#include "ast/nodes/compo/architecture.h"
#include "ast/nodes/compo/service.h"
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
				std::shared_ptr<compo::CArchitecture> m_architecture;

				std::vector<std::shared_ptr<CPort>> m_ports;

				/**< Vector of descriptor body nodes */
				std::vector<std::shared_ptr<compo::CService>> m_services;

				std::vector<std::shared_ptr<compo::CConstraint>> m_constraints;
			  public:
				/**
				* Parametric constructor with default values
				* @param name: name of descriptor
				* @param extends: name of parent descriptor
				                * @param architecture: architecture node
				                * @param ports: vector of ports
				                * @param services: vector of body service
				                * @param constraints: vector of body constraints
				*/
				CDescriptor(std::shared_ptr<procedural::CSymbol> name = nullptr,
				            std::shared_ptr<procedural::CSymbol> extends = nullptr,
				            std::shared_ptr<compo::CArchitecture> arch = nullptr,
				            const std::vector<std::shared_ptr<compo::CPort>>& ports = std::vector<std::shared_ptr<compo::CPort>>(0),
				            const std::vector<std::shared_ptr<compo::CService>>& services = std::vector<std::shared_ptr<compo::CService>>(0),
				            const std::vector<std::shared_ptr<compo::CConstraint>>& constraints = std::vector<std::shared_ptr<compo::CConstraint>>(0));

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				* Services vector size getter
				* @return number of services
				*/
				size_t getServicesSize() const;

				/**
				* Constraints vector size getter
							* @return number of constraints
							*/
				size_t getConstraintsSize() const;

				/**
				* Ports vector size getter
							* @return number of ports
							*/
				size_t getPortsSize() const;

				/**
				* Service getter
				* @return service
				*/
				std::shared_ptr<compo::CService> getServiceAt(size_t index) const;

				/**
				* Constraint getter
							* @return constraint
							*/
				std::shared_ptr<compo::CConstraint> getConstraintAt(size_t index) const;

				/**
				* Port getter
							* @return port
							*/
				std::shared_ptr<compo::CPort> getPortAt(size_t index) const;

				/**
				* Port getter
							* @return port
							*/
				std::shared_ptr<compo::CPort> getPortByName(const std::string& name) const;

				/**
				* Architecture getter
							* @return architecture
							*/
				std::shared_ptr<compo::CArchitecture> getArchitecture() const;

				/**
				* Service getter
							* @return service
							*/
				std::shared_ptr<compo::CService> getServiceByName(const std::string& name) const;
			};

		}

	}

}