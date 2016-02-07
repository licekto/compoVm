#pragma once

#include <iostream>
#include <vector>
#include <map>

enum NodeTypeEnum {
    END = 0,
    DESCRIPTOR,
    SYMBOL,
    SERVICE
};

const char * typeName(NodeTypeEnum type);

/*----------------------------------------------------------------------------*/

#define SYMBOL_VECTOR std::vector<CCompoSymbol*>
#define NODE_VECTOR std::vector<CCompoNode*>

/*----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------*/

class CCompoSymbol : public CCompoNode {
private:
            std::string         m_name;

public:
                                CCompoSymbol        (const std::string& name);
    virtual                     ~CCompoSymbol       () {};
    virtual void                print               (std::ostream& os) const;
            std::string         getName             () const;
};

/*----------------------------------------------------------------------------*/

class CCompoDescriptor : public CCompoNode {
private:
            CCompoSymbol      * m_name;
            CCompoSymbol      * m_extends;
            NODE_VECTOR         m_body;
            
public:
                                CCompoDescriptor    (CCompoSymbol *name, CCompoSymbol *extends, NODE_VECTOR body);
    virtual                     ~CCompoDescriptor   ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
            void                setExtends          (CCompoSymbol * extends);
            CCompoSymbol *      getExtends          () const;
};

/*----------------------------------------------------------------------------*/

class CCompoService : public CCompoNode {
private:
            CCompoSymbol      * m_name;
            SYMBOL_VECTOR       m_params;
            NODE_VECTOR         m_body;
            
public:
                                CCompoService       (CCompoSymbol *name, SYMBOL_VECTOR params, NODE_VECTOR body);
    virtual                     ~CCompoService      ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
            NODE_VECTOR *       getBody             ();
            void                setBody             (NODE_VECTOR body);
            SYMBOL_VECTOR *     getParams           ();
            void                setParam            (CCompoSymbol *param);
};

/*----------------------------------------------------------------------------*/