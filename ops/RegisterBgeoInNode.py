#
# Copyright 2018 Laika, LLC. Authored by Peter Stuart

# Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
# http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
# http://opensource.org/licenses/MIT>, at your option. This file may not be
# copied, modified, or distributed except according to those terms.
#

def buildHelp(filename):
    import os
    thispath = os.path.abspath(__file__)
    filepath = os.path.join(os.path.dirname(thispath), filename)
    with open(filepath, "r") as f:
        lines = f.readlines()
    return "\n".join(lines)


def registerBgeoIn():
    """
    Registers a new BgeoIn node type using the NodeTypeBuilder utility
    class.
    """

    from Katana import Nodes3DAPI
    from Katana import AssetAPI
    from Katana import FnAttribute
    from Katana import FnGeolibServices

    def buildBgeoInOpChain(node, interface):
        """
        Defines the callback function used to create the Ops chain for the
        node type being registered.

        @type node: C{Nodes3DAPI.NodeTypeBuilder.BgeoIn}
        @type interface: C{Nodes3DAPI.NodeTypeBuilder.BuildChainInterface}
        @param node: The node for which to define the Ops chain
        @param interface: The interface providing the functions needed to set
            up the Ops chain for the given node.
        """
        # Get the current frame time
        frameTime = interface.getGraphState().getTime()

        # Set the minimum number of input ports
        interface.setMinRequiredInputs(0)

        argsGb = FnAttribute.GroupBuilder()

        # Parse node parameters
        locationParam = node.getParameter('location')
        fileNameParam = node.getParameter('fileName')
        makeFacesetsParam = node.getParameter('makeFacesets')
        reportEmptyParam = node.getParameter('reportEmpty')
        computeBoundParam = node.getParameter('computePointCloudBound')
        createSubdParam = node.getParameter('createSubd')
        checkVersionParam = node.getParameter('checkVersion')
        
        # resolve file path so that it can include frame number replacement
        # i.e. %04d
        filePath = fileNameParam.getValue(frameTime)
        fileSequencePlugin = AssetAPI.GetDefaultFileSequencePlugin()
        if fileSequencePlugin and fileSequencePlugin.isFileSequence(filePath):
            fileSequence = fileSequencePlugin.getFileSequence(filePath)
            resolvedPath = fileSequence.getResolvedPath(int(frameTime))
        else:
            resolvedPath = filePath

        argsGb.set('fileName', FnAttribute.StringAttribute(resolvedPath))
        argsGb.set('makeFacesets', FnAttribute.IntAttribute(makeFacesetsParam.getValue(frameTime)))
        argsGb.set('reportEmpty', FnAttribute.IntAttribute(reportEmptyParam.getValue(frameTime)))
        argsGb.set('computePointCloudBound', FnAttribute.IntAttribute(computeBoundParam.getValue(frameTime)))
        argsGb.set('createSubd', FnAttribute.IntAttribute(createSubdParam.getValue(frameTime)))
        argsGb.set('checkVersion', FnAttribute.IntAttribute(checkVersionParam.getValue(frameTime)))

        # We want to use the StaticSceneCreate Op to build the parent
        # hierarchy, so that our op only has to worry about generating its
        # children. Its args are somewhat complex, but fortunately, there
        # is a helper class that makes it all much easier.

        rootLocation = locationParam.getValue(frameTime)

        sscb = FnGeolibServices.OpArgsBuilders.StaticSceneCreate()
        sscb.addSubOpAtLocation(rootLocation, 'BgeoIn', argsGb.build())

        interface.appendOp('StaticSceneCreate', sscb.build())

    # Create a NodeTypeBuilder to register the new type
    nodeTypeBuilder = Nodes3DAPI.NodeTypeBuilder('BgeoIn')

    nodeTypeBuilder.setHintsForNode({
        'help':buildHelp("BgeoInHelp.txt")
    })

    # Build the node's parameters
    gb = FnAttribute.GroupBuilder()
    gb.set('location',
           FnAttribute.StringAttribute('/root/world/geo/BgeoIn'))
    gb.set('fileName',
           FnAttribute.StringAttribute(''))
    gb.set('makeFacesets',
           FnAttribute.IntAttribute(0))
    gb.set('reportEmpty',
           FnAttribute.IntAttribute(1))
    gb.set('computePointCloudBound',
           FnAttribute.IntAttribute(0))
    gb.set('createSubd',
           FnAttribute.IntAttribute(1))
    gb.set('checkVersion',
           FnAttribute.IntAttribute(1))

    # Set the parameters template
    nodeTypeBuilder.setParametersTemplateAttr(gb.build())

    # Set parameter hints
    nodeTypeBuilder.setHintsForParameter('location', {
        'label':'Location',
        'widget':'scenegraphLocation'
    })
    nodeTypeBuilder.setHintsForParameter('fileName', {
        'label':'File Name',
        'widget':'fileInput'
    })
    nodeTypeBuilder.setHintsForParameter('makeFacesets',{
        'label':'Make Facesets',
        'widget':'checkBox',
        'help':'Create facesets from primitive groups.'
    })
    nodeTypeBuilder.setHintsForParameter('reportEmpty', {
        'label':'Report Empty Geometry',
        'widget':'checkBox',
        'help':'Report empty BGEO files (i.e. no geometry) as an error.'
    })
    nodeTypeBuilder.setHintsForParameter('computePointCloudBound', {
        'label':'Compute Point Cloud Bound',
        'widget':'checkBox',
        'help':'Compute the bound based on point P and width attributes, ' +
        'instead of using the embedded header bound. This will prevent ' +
        'points at the edges of the bound from be clipped. Enabling this ' +
        'option prevents deferred loading of the BGEO file.'
    })
    nodeTypeBuilder.setHintsForParameter('createSubd', {
        'label':'Create Subdivision Surfaces',
        'widget':'checkBox',
        'help':'Create subdivision surfaces for polymesh primitives.'
    })
    nodeTypeBuilder.setHintsForParameter('checkVersion', {
        'label':'Check Version',
        'widget':'checkBox',
        'help':'Verify the version in the bgeo file is compatible. ' +
        'Turn this off if you know the file is compatible regardless of ' +
        'the version it was written out from, i.e. from use of ' +
        'HOUDINIX_Y_GEO_COMPATIBILITY environment variables.'
    })

    # Set the callback responsible to build the Ops chain
    nodeTypeBuilder.setBuildOpChainFnc(buildBgeoInOpChain)

    # Build the new node type
    nodeTypeBuilder.build()

# Register the node
registerBgeoIn()
