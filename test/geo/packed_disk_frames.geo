["fileversion","15.5.482","hasindex",false,"pointcount",4,"vertexcount",4,"primitivecount",4,"info",
    {
	"artist":"vangogh",
	"primcount_summary":"          4 Packed Disks\n",
	"hostname":"zundert",
	"bounds":[-1.2000000500000001,1.2000000500000001,-1.2000000500000001,1.2000000500000001,-1.2000000500000001,1.2000000500000001
	],
	"attribute_summary":"     1 point attributes:\tP\n     1 primitive attributes:\tpath\n",
	"date":"2016-09-21 09:43:02",
	"software":"Houdini 15.5.482"
    },"topology",
    ["pointref",
	["indices",
	    [0,1,2,3
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
		    ["size",3,"storage","fpreal64","values",
			[0,0,0
			]
		    ],"values",
		    ["size",3,"storage","fpreal32","tuples",
			[
			    [0,0,0
			    ],
			    [0,0,0
			    ],
			    [0,0,0
			    ],
			    [0,0,0
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
		    ["sphere.%F.bgeo","sphere.%F4.bgeo"
		    ],"indices",
		    ["size",1,"storage","int32","arrays",
			[
			    [0,1,0,1
			    ]
			]
		    ]
		]
	    ]
	]
    ],"primitives",
    [
	[
	    ["type","run","runtype","PackedDisk","varyingfields",
		["parameters","vertex"
		],"uniformfields",
		{
		    "viewportlod":"full",
		    "pivot":[0,0,0
		    ],
		    "transform":[1,0,0,0,1,0,0,0,1
		    ]
		}
	    ],
	    [
		[
		    {
			"expandfilename":true,
			"pointinstancetransform":false,
			"expandframe":11,
			"filename":"sphere.$F.bgeo"
		    },0
		],
		[
		    {
			"expandfilename":true,
			"pointinstancetransform":false,
			"expandframe":11,
			"filename":"sphere.$F4.bgeo"
		    },1
		],
		[
		    {
			"expandfilename":true,
			"pointinstancetransform":false,
			"expandframe":5,
			"filename":"sphere.$F.bgeo"
		    },2
		],
		[
		    {
			"expandfilename":true,
			"pointinstancetransform":false,
			"expandframe":5,
			"filename":"sphere.$F4.bgeo"
		    },3
		]
	    ]
	]
    ],"sharedprimitivedata",
    [
    ]
]
