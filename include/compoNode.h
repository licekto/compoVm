#pragma once

#include <iostream>

enum NodeTypeEnum {
    END = 0,
    DESCRIPTOR,
    SYMBOL
};

const char * typeName(NodeTypeEnum type);

class CCompoNode {
protected:
            NodeTypeEnum        m_type;
            bool                m_toString;

public:
                                CCompoNode          (NodeTypeEnum type);
    virtual                     ~CCompoNode         () {};
    virtual void                print               (std::ostream& os) const = 0;
    friend  std::ostream&       operator <<         (std::ostream& os, const CCompoNode& node);
};

class CCompoSymbol : public CCompoNode {
private:
            std::string         m_name;

public:
                                CCompoSymbol        (const std::string& name);
    virtual                     ~CCompoSymbol       () {};
            std::string         getName             () const;
    virtual void                print               (std::ostream& os) const;
};

class CCompoDescriptor : public CCompoNode {
private:
            CCompoSymbol      * m_name;
            CCompoSymbol      * m_extends;
            CCompoNode        * m_body;
            
public:
                                CCompoDescriptor    (CCompoSymbol *name, CCompoSymbol *extends, CCompoNode *body);
    virtual                     ~CCompoDescriptor   ();
            CCompoSymbol *      getName             () const;
    virtual void                print               (std::ostream& os) const;
            void                setExtends          (CCompoSymbol * extends);
            CCompoSymbol *      getExtends          () const;
};