["fileversion","16.0.450","hasindex",false,"pointcount",2,"vertexcount",2,"primitivecount",2,"info",
    {
	"volume_summary":"Volume Resolutions:\n  0 (density) : [4, 3, 3] Voxel Count: 36\n  1 (density) : [4, 3, 3] Voxel Count: 36\n",
	"artist":"vangogh",
	"primcount_summary":"          2 Volumes\n",
	"hostname":"zundert",
	"bounds":[-1.99180066999999994,4.89180087999999991,-1.49385046999999993,1.49385046999999993,-1.49385046999999993,1.49385046999999993
	],
	"attribute_summary":"     1 point attributes:\tP\n     1 primitive attributes:\tname\n",
	"date":"2017-04-05 08:43:44",
	"software":"Houdini 16.0.450"
    },"topology",
    ["pointref",
	["indices",
	    [0,1
	    ]
	]
    ],"attributes",
    ["pointattributes",
	[
	    [
		["scope","public","type","numeric","name","P","options",
		    {
			"type":{
			    "type":"string",
			    "value":"point"
			}
		    }
		],
		["size",3,"storage","fpreal32","defaults",
		    ["size",1,"storage","fpreal64","values",
			[0
			]
		    ],"values",
		    ["size",3,"storage","fpreal32","tuples",
			[
			    [0,0,0
			    ],
			    [2.90000010000000019,0,0
			    ]
			]
		    ]
		]
	    ]
	],"primitiveattributes",
	[
	    [
		["scope","public","type","string","name","name","options",
		    {
		    }
		],
		["size",1,"storage","int32","strings",
		    ["density"
		    ],"indices",
		    ["size",1,"storage","int32","arrays",
			[
			    [0,0
			    ]
			]
		    ]
		]
	    ]
	]
    ],"primitives",
    [
	[
	    ["type","Volume"
	    ],
	    ["vertex",0,"transform",
		[1.99180066999999994,0,0,0,1.49385046999999993,0,0,0,1.49385046999999993
		],"res",
		[4,3,3
		],"border",
		{
		    "type":"constant",
		    "value":0
		},"compression",
		{
		    "tolerance":0
		},"sharedvoxels","voxels:0x7fdaa5234100","visualization",
		{
		    "iso":0,
		    "mode":"smoke",
		    "density":1
		},"taperx",1,"tapery",1
	    ]
	],
	[
	    ["type","Volume"
	    ],
	    ["vertex",1,"transform",
		[1.99180066999999994,0,0,0,1.49385046999999993,0,0,0,1.49385046999999993
		],"res",
		[4,3,3
		],"border",
		{
		    "type":"constant",
		    "value":0
		},"compression",
		{
		    "tolerance":0
		},"sharedvoxels","voxels:0x7fdaa5233f00","visualization",
		{
		    "iso":0,
		    "mode":"smoke",
		    "density":1
		},"taperx",1,"tapery",1
	    ]
	]
    ],"sharedprimitivedata",
    ["Volume",
	["geo:voxels","voxels:0x7fdaa5234100",
	    ["tiledarray",
		["version",1,"compressiontypes",
		    ["raw","rawfull","constant","fpreal16","FP32Range"
		    ],"tiles",
		    [
			["compression",0,"data",
			    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.234147369999999994,0.143372312000000002,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			    ]
			]
		    ]
		]
	    ]
	],"Volume",
	["geo:voxels","voxels:0x7fdaa5233f00",
	    ["tiledarray",
		["version",1,"compressiontypes",
		    ["raw","rawfull","constant","fpreal16","FP32Range"
		    ],"tiles",
		    [
			["compression",0,"data",
			    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.292123287999999981,0.178871945000000004,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			    ]
			]
		    ]
		]
	    ]
	]
    ]
]
