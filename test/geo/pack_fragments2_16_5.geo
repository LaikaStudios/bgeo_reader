["fileversion","16.5.268","hasindex",false,"pointcount",2,"vertexcount",2,"primitivecount",2,"info",
    {
	"artist":"vangogh",
	"primcount_summary":"          2 Packed Fragments\n",
	"hostname":"zundert",
	"bounds":[-0.5,0.5,-0.5,0.5,-0.5,0.5
	],
	"attribute_summary":"     2 point attributes:\tP, name\n     1 primitive attributes:\tpath\n",
	"date":"2017-11-15 14:45:04",
	"software":"Houdini 16.5.268"
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
			    [0,0,0
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
		    ["piece0","piece1"
		    ],"indices",
		    ["size",1,"storage","int32","arrays",
			[
			    [0,1
			    ]
			]
		    ]
		]
	    ]
	],"primitiveattributes",
	[
	    [
		["scope","public","type","string","name","path","options",
		    {
		    }
		],
		["size",1,"storage","int32","strings",
		    ["op:/obj/packed/assemble2/pack/piece0","op:/obj/packed/assemble2/pack/piece1"
		    ],"indices",
		    ["size",1,"storage","int32","arrays",
			[
			    [0,1
			    ]
			]
		    ]
		]
	    ]
	]
    ],"primitives",
    [
	[
	    ["type","PackedFragment"
	    ],
	    ["parameters",
		{
		    "name":"piece0",
		    "embedded":"embed:0x7f71fc6f0f00",
		    "attribute":"name",
		    "bounds":[-0.5,0.5,-0.5,0.5,-0.5,0.5
		    ],
		    "pointinstancetransform":false,
		    "cachedbounds":[-0.5,0.5,-0.5,0.5,-0.5,0.5
		    ]
		},"pivot",
		[0,0,0
		],"transform",
		[1,0,0,0,1,0,0,0,1
		],"vertex",0,"viewportlod","full"
	    ]
	],
	[
	    ["type","PackedFragment"
	    ],
	    ["parameters",
		{
		    "name":"piece1",
		    "embedded":"embed:0x7f71fc6f0f00",
		    "attribute":"name",
		    "bounds":[-0.5,0.5,-0.5,0.5,-0.5,0.5
		    ],
		    "pointinstancetransform":false,
		    "cachedbounds":[-0.5,0.5,-0.5,0.5,-0.5,0.5
		    ]
		},"pivot",
		[0,0,0
		],"transform",
		[1,0,0,0,1,0,0,0,1
		],"vertex",1,"viewportlod","full"
	    ]
	]
    ],"sharedprimitivedata",
    ["PackedFragment",
	["gu:embeddedgeo","embed:0x7f71fc6f0f00",
	    ["fileversion","16.5.268","hasindex",false,"pointcount",20,"vertexcount",36,"primitivecount",10,"info",
		{
		    "artist":"vangogh",
		    "primcount_summary":"         10 Polygons\n",
		    "hostname":"zundert",
		    "bounds":[-0.5,0.5,-0.5,0.5,-0.5,0.5
		    ],
		    "attribute_summary":"     1 vertex attributes:\tN\n     1 point attributes:\tP\n     2 primitive attributes:\tname, Cd\n     1 global attributes:\tvarmap\n",
		    "date":"2017-11-15 14:45:04",
		    "group_summary":"     2 primitive groups:\tinside\n\toutside\n",
		    "software":"Houdini 16.5.268"
		},"topology",
		["pointref",
		    ["indices",
			[1,4,3,0,2,5,4,1,4,5,3,2,1,0,14,15,13,12,8,11,10,7,6,9,11,8,7,6,8,10,11,9,19,18,16,17
			]
		    ]
		],"attributes",
		["vertexattributes",
		    [
			[
			    ["scope","public","type","numeric","name","N","options",
				{
				    "type":{
					"type":"string",
					"value":"normal"
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
					[0,0,-1
					],
					[0,0,-1
					],
					[0,0,-1
					],
					[0,0,-1
					],
					[1,0,0
					],
					[1,0,0
					],
					[1,0,0
					],
					[1,0,0
					],
					[0,1,0
					],
					[0,1,0
					],
					[0,1,0
					],
					[0,-1,0
					],
					[0,-1,0
					],
					[0,-1,0
					],
					[-0.707106828999999992,0,0.707106828999999992
					],
					[-0.707106828999999992,0,0.707106828999999992
					],
					[-0.707106828999999992,0,0.707106828999999992
					],
					[-0.707106828999999992,0,0.707106828999999992
					],
					[0,0,1
					],
					[0,0,1
					],
					[0,0,1
					],
					[0,0,1
					],
					[-1,0,0
					],
					[-1,0,0
					],
					[-1,0,0
					],
					[-1,0,0
					],
					[0,-1,0
					],
					[0,-1,0
					],
					[0,-1,0
					],
					[0,1,0
					],
					[0,1,0
					],
					[0,1,0
					],
					[0.707106828999999992,0,-0.707106828999999992
					],
					[0.707106828999999992,0,-0.707106828999999992
					],
					[0.707106828999999992,0,-0.707106828999999992
					],
					[0.707106828999999992,0,-0.707106828999999992
					]
				    ]
				]
			    ]
			]
		    ],"pointattributes",
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
					[-0.5,-0.5,-0.5
					],
					[0.5,-0.5,-0.5
					],
					[0.5,-0.5,0.5
					],
					[-0.5,0.5,-0.5
					],
					[0.5,0.5,-0.5
					],
					[0.5,0.5,0.5
					],
					[-0.5,-0.5,-0.5
					],
					[0.5,-0.5,0.5
					],
					[-0.5,-0.5,0.5
					],
					[-0.5,0.5,-0.5
					],
					[0.5,0.5,0.5
					],
					[-0.5,0.5,0.5
					],
					[-0.5,-0.5,-0.5
					],
					[0.5,-0.5,0.5
					],
					[-0.5,0.5,-0.5
					],
					[0.5,0.5,0.5
					],
					[-0.5,-0.5,-0.5
					],
					[0.5,-0.5,0.5
					],
					[-0.5,0.5,-0.5
					],
					[0.5,0.5,0.5
					]
				    ]
				]
			    ]
			]
		    ],"primitiveattributes",
		    [
			[
			    ["scope","public","type","numeric","name","Cd","options",
				{
				    "type":{
					"type":"string",
					"value":"color"
				    }
				}
			    ],
			    ["size",3,"storage","fpreal32","defaults",
				["size",1,"storage","fpreal64","values",
				    [1
				    ]
				],"values",
				["size",3,"storage","fpreal32","tuples",
				    [
					[0.641600609000000044,0.641600609000000044,0.641600609000000044
					],
					[0.641600609000000044,0.641600609000000044,0.641600609000000044
					],
					[0.641600609000000044,0.641600609000000044,0.641600609000000044
					],
					[0.641600609000000044,0.641600609000000044,0.641600609000000044
					],
					[0.641600609000000044,0.641600609000000044,0.641600609000000044
					],
					[0.80046379599999995,0.60630786400000003,0.212691425999999989
					],
					[0.80046379599999995,0.60630786400000003,0.212691425999999989
					],
					[0.80046379599999995,0.60630786400000003,0.212691425999999989
					],
					[0.80046379599999995,0.60630786400000003,0.212691425999999989
					],
					[0.80046379599999995,0.60630786400000003,0.212691425999999989
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
				["piece0","piece1"
				],"indices",
				["size",1,"storage","int32","arrays",
				    [
					[0,0,0,0,0,1,1,1,1,1
					]
				    ]
				]
			    ]
			]
		    ],"globalattributes",
		    [
			[
			    ["scope","public","type","string","name","varmap","options",
				{
				}
			    ],
			    ["size",1,"storage","int32","strings",
				["name -> NAME"
				],"indices",
				["size",1,"storage","int32","arrays",
				    [
					[0
					]
				    ]
				]
			    ]
			]
		    ]
		],"primitives",
		[
		    [
			["type","Polygon_run"
			],
			["startvertex",0,"nprimitives",10,"nvertices",
			    [4,4,3,3,4,4,4,3,3,4
			    ]
			]
		    ]
		],"primitivegroups",
		[
		    [
			["name","inside"
			],
			["selection",
			    ["unordered",
				["i8",
				    [0,0,0,0,1,0,0,0,0,1
				    ]
				]
			    ]
			]
		    ],
		    [
			["name","outside"
			],
			["selection",
			    ["unordered",
				["i8",
				    [1,1,1,1,0,1,1,1,1,0
				    ]
				]
			    ]
			]
		    ]
		]
	    ]
	]
    ]
]
