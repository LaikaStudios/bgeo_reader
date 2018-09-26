["fileversion","16.0.450","hasindex",false,"pointcount",7,"vertexcount",7,"primitivecount",7,"info",
    {
	"volume_summary":"Volume Resolutions:\n  0 (density) : [4, 7, 4] Voxel Count: 112\n  1 (vel.x) : [4, 7, 4] Voxel Count: 112\n  2 (vel.y) : [4, 7, 4] Voxel Count: 112\n  3 (vel.z) : [4, 7, 4] Voxel Count: 112\n  4 (temperature) : [4, 7, 4] Voxel Count: 112\n  5 (heat) : [4, 7, 4] Voxel Count: 112\n  6 (fuel) : [4, 7, 4] Voxel Count: 112\n",
	"artist":"vangogh",
	"primcount_summary":"          7 Volumes\n",
	"hostname":"zundert",
	"bounds":[-2.79101801000000016,2.31961298000000005,-0.688791275000000036,8.65636253000000089,-2.62832451000000011,2.62832451000000011
	],
	"attribute_summary":"     1 point attributes:\tP\n     2 primitive attributes:\tname, dopobject\n     5 global attributes:\trest_ratio, varmap, doppath, rest2_ratio, timescale\n",
	"date":"2017-04-05 08:42:56",
	"group_summary":"     1 primitive groups:\tpyro\n",
	"software":"Houdini 16.0.450"
    },"topology",
    ["pointref",
	["indices",
	    [0,1,2,3,4,5,6
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
		    ["size",4,"storage","fpreal64","values",
			[0,0,0,1
			]
		    ],"values",
		    ["size",3,"storage","fpreal32","tuples",
			[
			    [-0.235702515000000001,3.98378562999999986,0
			    ],
			    [-0.235702515000000001,3.98378562999999986,0
			    ],
			    [-0.235702515000000001,3.98378562999999986,0
			    ],
			    [-0.235702515000000001,3.98378562999999986,0
			    ],
			    [-0.235702515000000001,3.98378562999999986,0
			    ],
			    [-0.235702515000000001,3.98378562999999986,0
			    ],
			    [-0.235702515000000001,3.98378562999999986,0
			    ]
			]
		    ]
		]
	    ]
	],"primitiveattributes",
	[
	    [
		["scope","public","type","string","name","dopobject","options",
		    {
		    }
		],
		["size",1,"storage","int32","strings",
		    ["/obj/AutoDopNetwork:0"
		    ],"indices",
		    ["size",1,"storage","int32","arrays",
			[
			    [0,0,0,0,0,0,0
			    ]
			]
		    ]
		]
	    ],
	    [
		["scope","public","type","string","name","name","options",
		    {
		    }
		],
		["size",1,"storage","int32","strings",
		    ["density","vel.x","vel.y","vel.z","temperature","heat","fuel"
		    ],"indices",
		    ["size",1,"storage","int32","arrays",
			[
			    [0,1,2,3,4,5,6
			    ]
			]
		    ]
		]
	    ]
	],"globalattributes",
	[
	    [
		["scope","public","type","string","name","doppath","options",
		    {
		    }
		],
		["size",1,"storage","int32","strings",
		    ["/obj/AutoDopNetwork/pyro/emptyobject7"
		    ],"indices",
		    ["size",1,"storage","int32","arrays",
			[
			    [0
			    ]
			]
		    ]
		]
	    ],
	    [
		["scope","public","type","numeric","name","rest2_ratio","options",
		    {
		    }
		],
		["size",1,"storage","fpreal32","defaults",
		    ["size",1,"storage","fpreal64","values",
			[0
			]
		    ],"values",
		    ["size",1,"storage","fpreal32","arrays",
			[
			    [1
			    ]
			]
		    ]
		]
	    ],
	    [
		["scope","public","type","numeric","name","rest_ratio","options",
		    {
		    }
		],
		["size",1,"storage","fpreal32","defaults",
		    ["size",1,"storage","fpreal64","values",
			[0
			]
		    ],"values",
		    ["size",1,"storage","fpreal32","arrays",
			[
			    [0
			    ]
			]
		    ]
		]
	    ],
	    [
		["scope","public","type","numeric","name","timescale","options",
		    {
		    }
		],
		["size",1,"storage","fpreal32","defaults",
		    ["size",1,"storage","fpreal64","values",
			[0
			]
		    ],"values",
		    ["size",1,"storage","fpreal32","arrays",
			[
			    [1
			    ]
			]
		    ]
		]
	    ],
	    [
		["scope","public","type","string","name","varmap","options",
		    {
		    }
		],
		["size",5,"storage","int32","strings",
		    ["dopobject -> DOPOBJECT","doppath -> DOPPATH","timescale -> TIMESCALE","rest_ratio -> REST_RATIO","rest2_ratio -> REST2_RATIO"
		    ],"indices",
		    ["size",5,"storage","int32","tuples",
			[
			    [0,1,2,3,4
			    ]
			]
		    ]
		]
	    ]
	]
    ],"primitives",
    [
	[
	    ["type","run","runtype","Volume","varyingfields",
		["vertex","border","compression","sharedvoxels","visualization"
		],"uniformfields",
		{
		    "taperx":1,
		    "res":[4,7,4
		    ],
		    "transform":[2.55531549453735352,0,0,0,4.672576904296875,0,0,0,2.62832450866699219
		    ],
		    "tapery":1
		}
	    ],
	    [
		[0,
		    {
			"type":"constant",
			"value":0
		    },
		    {
			"tolerance":0
		    },"voxels:0x7f22f8e33f00",
		    {
			"iso":0,
			"mode":"smoke",
			"density":1
		    }
		],
		[1,
		    {
			"type":"constant",
			"value":0
		    },
		    {
			"tolerance":0
		    },"voxels:0x7f22f8e34480",
		    {
			"iso":0,
			"mode":"invisible",
			"density":1
		    }
		],
		[2,
		    {
			"type":"constant",
			"value":0
		    },
		    {
			"tolerance":0
		    },"voxels:0x7f22f8e34500",
		    {
			"iso":0,
			"mode":"invisible",
			"density":1
		    }
		],
		[3,
		    {
			"type":"constant",
			"value":0
		    },
		    {
			"tolerance":0
		    },"voxels:0x7f22f8e34580",
		    {
			"iso":0,
			"mode":"invisible",
			"density":1
		    }
		],
		[4,
		    {
			"type":"constant",
			"value":0
		    },
		    {
			"tolerance":0
		    },"voxels:0x7f22f8e34600",
		    {
			"iso":0,
			"mode":"invisible",
			"density":1
		    }
		],
		[5,
		    {
			"type":"constant",
			"value":-0.00999999977648258209
		    },
		    {
			"tolerance":0
		    },"voxels:0x7f22f8e34680",
		    {
			"iso":0,
			"mode":"smoke",
			"density":1
		    }
		],
		[6,
		    {
			"type":"constant",
			"value":0
		    },
		    {
			"tolerance":0
		    },"voxels:0x7f22f8e34700",
		    {
			"iso":0,
			"mode":"invisible",
			"density":1
		    }
		]
	    ]
	]
    ],"primitivegroups",
    [
	[
	    ["name","pyro"
	    ],
	    ["selection",
		["unordered",
		    ["i8",
			[1,1,1,1,1,1,1
			]
		    ]
		]
	    ]
	]
    ],"sharedprimitivedata",
    ["Volume",
	["geo:voxels","voxels:0x7f22f8e33f00",
	    ["tiledarray",
		["version",1,"compressiontypes",
		    ["raw","rawfull","constant","fpreal16","FP32Range"
		    ],"tiles",
		    [
			["compression",0,"data",
			    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0737045109000000059,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.025658134400000001,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			    ]
			]
		    ]
		]
	    ]
	],"Volume",
	["geo:voxels","voxels:0x7f22f8e34480",
	    ["constantarray",0
	    ]
	],"Volume",
	["geo:voxels","voxels:0x7f22f8e34500",
	    ["constantarray",0
	    ]
	],"Volume",
	["geo:voxels","voxels:0x7f22f8e34580",
	    ["constantarray",0
	    ]
	],"Volume",
	["geo:voxels","voxels:0x7f22f8e34600",
	    ["tiledarray",
		["version",1,"compressiontypes",
		    ["raw","rawfull","constant","fpreal16","FP32Range"
		    ],"tiles",
		    [
			["compression",0,"data",
			    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.817695021999999994,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.286854804000000019,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			    ]
			]
		    ]
		]
	    ]
	],"Volume",
	["geo:voxels","voxels:0x7f22f8e34680",
	    ["tiledarray",
		["version",1,"compressiontypes",
		    ["raw","rawfull","constant","fpreal16","FP32Range"
		    ],"tiles",
		    [
			["compression",0,"data",
			    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.0737045109000000059,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.025658134400000001,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			    ]
			]
		    ]
		]
	    ]
	],"Volume",
	["geo:voxels","voxels:0x7f22f8e34700",
	    ["tiledarray",
		["version",1,"compressiontypes",
		    ["raw","rawfull","constant","fpreal16","FP32Range"
		    ],"tiles",
		    [
			["compression",0,"data",
			    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.747675717000000017,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0.262479573000000022,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
			    ]
			]
		    ]
		]
	    ]
	]
    ]
]
