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
            CCompoNode        * m_body;
            
public:
                                CCompoDescriptor    (CCompoSymbol *name, CCompoSymbol *extends, CCompoNode *body);
    virtual                     ~CCompoDescriptor   ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
            void                setExtends          (CCompoSymbol * extends);
            CCompoSymbol *      getExtends          () const;
};

/*----------------------------------------------------------------------------*/

#define SYMBOL_VECTOR std::vector<CCompoSymbol*>

class CCompoService : public CCompoNode {
private:
            CCompoSymbol      * m_name;
            SYMBOL_VECTOR       m_params;
            CCompoNode        * m_body;
            
public:
                                CCompoService       (CCompoSymbol *name, SYMBOL_VECTOR params, CCompoNode *body);
    virtual                     ~CCompoService      ();
    virtual void                print               (std::ostream& os) const;
            CCompoSymbol *      getName             () const;
            CCompoNode *        getBody             () const;
            void                setBody             (CCompoNode *body);
            SYMBOL_VECTOR *     getParams           ();
            void                setParam            (CCompoSymbol *param);
};

/*----------------------------------------------------------------------------*/