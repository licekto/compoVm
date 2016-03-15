#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/compo/port.h"
#include "ast/procedural/symbol.h"
#include "ast/compo/signaturesPort.h"
#include "ast/compo/serviceSignature.h"
#include "abstractReqProv.h"
#include "provision.h"
#include "requirement.h"
#include "architecture.h"

namespace ast {

	namespace compo {

		/**
		 * \class CDescriptor
		 * \brief Class for Compo descriptor representation.
		 */
		class CDescriptor : public CNode {
		  private:
			/**< Descriptor name */
			std::shared_ptr<ast::procedural::CSymbol> m_name;

			/**< Inheritance information */
			std::shared_ptr<ast::procedural::CSymbol> m_extends;

			std::shared_ptr<ast::compo::CProvision> m_interalProvision;

			std::shared_ptr<ast::compo::CProvision> m_exteralProvision;

			std::shared_ptr<ast::compo::CRequirement> m_interalRequirement;

			std::shared_ptr<ast::compo::CRequirement> m_exteralRequirement;

			std::shared_ptr<ast::compo::CArchitecture> m_architecture;

			/**< Vector of descriptor body nodes */
			std::vector<std::shared_ptr<ast::compo::CService>> m_services;

			std::vector<std::shared_ptr<ast::compo::CConstraint>> m_constraints;

			/**< Every descriptor contains default port */
			std::shared_ptr<ast::compo::CPort> m_defaultPort;

		  public:
			/**
			* Parametric constructor with default values
			* @param name: name of descriptor
			* @param extends: name of parent descriptor
			* @param body: vector of body nodes
			*/
			CDescriptor(std::shared_ptr<ast::procedural::CSymbol> name = nullptr,
			            std::shared_ptr<ast::procedural::CSymbol> extends = nullptr,
			            std::shared_ptr<ast::compo::CProvision> inProv = nullptr,
			            std::shared_ptr<ast::compo::CProvision> exProv = nullptr,
			            std::shared_ptr<ast::compo::CRequirement> inReq = nullptr,
			            std::shared_ptr<ast::compo::CRequirement> exReq = nullptr,
			            std::shared_ptr<ast::compo::CArchitecture> arch = nullptr,
			            const std::vector<std::shared_ptr<ast::compo::CService>>& services = std::vector<std::shared_ptr<ast::compo::CService>>(0),
			            const std::vector<std::shared_ptr<ast::compo::CConstraint>>& constraints = std::vector<std::shared_ptr<ast::compo::CConstraint>>(0));

			/**
			* Accept method for visitor acceptation.
			* @param visitor: Pointer to abstract visitor.
			*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			* Name getter
			* @return name symbol
			*/
			std::string getName() const;

			/**
			* Extends getter
			* @return name of parent class symbol
			*/
			std::string getExtends() const;

			/**
			 * Body vector size getter
			 * @return number of elements in body
			 */
			size_t getServicesSize () const;

			size_t getConstraintsSize () const;

			/**
			* Body getter
			* @return Constant pointer to body vector
			*/
			std::shared_ptr<ast::compo::CService> getServiceAt (int index) const;

			std::shared_ptr<ast::compo::CConstraint> getConstraintAt (int index) const;

			std::shared_ptr<ast::compo::CProvision> getInProvision() const;

			std::shared_ptr<ast::compo::CProvision> getExProvision() const;

			std::shared_ptr<ast::compo::CRequirement> getInRequirement() const;

			std::shared_ptr<ast::compo::CRequirement> getExRequirement() const;

			std::shared_ptr<ast::compo::CArchitecture> getArchitecture() const;

			/**
			* Default port getter
			            * @return Constant pointer to port
			            */
			std::shared_ptr<ast::compo::CPort> getDefaultPort() const;
		};

	}

}