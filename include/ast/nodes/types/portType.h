#pragma once

namespace ast {
    
    namespace nodes {

	namespace types {

		/**
		 * \enum portType
		 * \brief Types of ports
		 */
		enum portType {
			EXPLICIT_LIST,
			UNIVERSAL,
			NAMED,
			INJECTED,
		};

	}
        
    }

}