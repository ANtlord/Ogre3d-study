#ifndef SUPERLISTENER_H
#define SUPERLISTENER_H

#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <OgreMaterial.h>
#include <OgreString.h>
#include <OgreRenderable.h>
#include <OgreShaderGenerator.h>

class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
{
public:
    ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator);

    /** This is the hook point where shader based technique will be created.
        It will be called whenever the material manager won't find appropriate technique
        that satisfy the target scheme name. If the scheme name is out target RT Shader System
        scheme name we will try to create shader generated technique for it.
    */
    virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
          const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex,
          const Ogre::Renderable* rend);

protected:
    Ogre::RTShader::ShaderGenerator * mShaderGenerator;                       // The shader generator instance.
};

#endif //SUPERLISTENER_H
