#pragma once

namespace interpreter {

	namespace core {
		enum coreModuleType {
			COLLECTION_PORT,
			COMPONENT,
			CONNECTION_DESCRIPTION,
			DESCRIPTOR,
			INTERFACE,
			PORT,
			PORT_DESCRIPTION,
			SERVICE,
			SERVICE_SIGNATURE,
		};
	}
}