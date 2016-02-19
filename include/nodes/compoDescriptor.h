#pragma once

#include "compoNode.h"
#include "compoSymbol.h"

/**
 * \class CCompoDescriptor
 * \brief Class for Compo descriptor representation.
 */
class CCompoDescriptor : public CCompoNode {
private:
            CCompoSymbol                  * m_name;         /**< Descriptor name */
            CCompoSymbol                  * m_extends;      /**< Inheritance information */
            std::vector<CCompoNode*>        m_body;         /**< Vector of descriptor body nodes */
            
public:
                                            /**
                                            * Parametric constructor with default values
                                            * @param name: Name of descriptor
                                            * @param extends: Name of parent descriptor
                                            * @param body: Vector of body nodes
                                            */
                                            CCompoDescriptor    (   CCompoSymbol *name = nullptr,
                                                                    CCompoSymbol *extends = nullptr,
                                                                    const std::vector<CCompoNode*>& body = std::vector<CCompoNode*>(0));
                                            /**
                                            * Virtual destructor
                                            */
    virtual                                 ~CCompoDescriptor   ();
                                            /**
                                            * Virtual print function to call from operator <<
                                            * @param os: output stream
                                            * @see operator <<()
                                            */
    virtual void                            print               (std::ostream& os) const;
                                            /**
                                            * Name getter
                                            * @return Name symbol 
                                            */
            CCompoSymbol *                  getName             () const;
                                            /**
                                            * Extends setter
                                            * @param Name of parent class symbol 
                                            */
            void                            setExtends          (CCompoSymbol * extends);
                                            /**
                                            * Extends getter
                                            * @return Name of parent class symbol 
                                            */
            CCompoSymbol *                  getExtends          () const;
                                            /**
                                            * Body getter
                                            * @return Constant pointer to body vector
                                            */
            std::vector<CCompoNode*> *      getBody             () const;
};