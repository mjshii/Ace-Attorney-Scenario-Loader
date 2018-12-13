# Ace Attorney Scenario Loader
[TOC]

### Available Commands

All available commands in the scenario files can be seen below:

```json
{
    "inventory": [
        {
            "name": "Name of the item",
            "image": "Item image (optional, if not specified will use name + .png)",
            "type": "Details on kind and where received",
            "desc": "A detailed description of the item"
        }
        // ... as many more as you want
    ],
    "story": [
        {
            // choose any number of the below commands
            "bg": "background_image.png",
            "bgm": "looping_background_music.mp3",
            "sfx": "sound_effect_that_plays_once.mp3",
            "name": "Name of the guy who's talking",
            "image": "Their sprite picture",
            "text": "The contents of their speech",
            "overlay": "An image that shows up over them",
            "shout": "An image that shows up over the overlay",
            "add item": {
                "name": "the usual",
                "image": "the usual",
                // ... etc
            },
            "remove item": ["one", "or", "many item names"],
        },
        {
            "text": "another block, but bg, bgm, name, image, and overlay persist to here so I can just type out some dialogue. Clear those out by setting them to an empty string."
        },
        // ...
        // repeat as many times as you want
        // ...
        {
            "testimony": {
                "default present": [
                    {
                        "name": "A disapproving judge",
                        "text": "A block that shows up when you present an invalid item. All the normal rules apply"
                    }
                    // as long as you want, as above
                ],
                "afterword": [
                    {
                        "text": "What the attorneys say after the guy has given his testimony"
                    }
                    // as long as you want, as above
                ],
                "short afterword": [
                    {
                        "text": "A summary of the above so the player doesn't have to keep pressing buttons"
                    }
                ],
                "statements": [
                    {
                        "text": "Statement number 1",
                        "press": [
                            {
                                "text": "These show up when you press statement number 1"
                            },
                            {
                                "text": "and can be as long as you want"
                            }
                        ],
                        "present item1": [
                            {
                                "text": "This shows up only when the player presents the item named item1 here."
                            },
                            {
                                "text": "You can have a statement block without any present text."
                            },
                        ]
                    },
                    {
                        "text": "Statement number 2",
                        // this statement only shows up if you press statement 1 and has no special present dialogue
                        "condition": 1,
                        "press": [
                            {
                                "text": "Nothing much to say..."
                            },
                            {
                                "text": "But here's an item!"
                            },
                            {
                                "add item": {
                                    "name": "Some Item",
                                    "desc": "Something to present if you want to leave the loop"
                                }
                            }
                        ]
                    }
                    {
                        "text": "Statement number 3",
                        "press": [
                            {
                                "text": "If you present Some Item here, you win!"
                            }
                        ],
                        "present Some Item": [
                            {
                                "text": "Hip hip hurrah"
                            },
                            {
                                "cmd": "exit"
                            }
                        ]
                    }
                ]
            }
        },
        {
			"text": "You broke out of the loop! Congrats"
        },
        {
			"text": "That's the end of it now."
        }
    ]
}
```



### Playable version

Here's a playable version of the above:

```json
{
	"inventory": [{
		"name": "report",
		"type": "Type: Documents <br> Received from a shady officer on an unnamed street corner.",
		"desc": "a report on the body"
	}],
	"story": [{
			"bg": "background_image.png",
			"bgm": "looping_background_music.mp3",
			"sfx": "sound_effect_that_plays_once.mp3",
			"name": "Name of the guy who's talking",
			"image": "Their sprite picture",
			"text": "The contents of their speech",
			"overlay": "An image that shows up over them",
			"shout": "An image that shows up over the overlay",
			"add item": {
				"name": "the usual",
				"image": "the usual"
			},
			"remove item": ["one", "or", "many item names"]
		},
		{
			"text": "another block, but bg, bgm, name, image, and overlay persist to here so I can just type out some dialogue. Clear those out by setting them to an empty string."
		},
		{
			"testimony": {
				"default present": [{
					"name": "A disapproving judge",
					"text": "A block that shows up when you present an invalid item. All the normal rules apply"
				}],
				"afterword": [{
					"text": "What the attorneys say after the guy has given his testimony"
				}],
				"short afterword": [{
					"text": "A summary of the above so the player doesn't have to keep pressing buttons"
				}],
				"statements": [{
						"text": "Statement number 1",
						"press": [{
								"text": "These show up when you press statement number 1"
							},
							{
								"text": "and can be as long as you want"
							}
						],
						"present item1": [{
								"text": "This shows up only when the player presents the item named item1 here."
							},
							{
								"text": "You can have a statement block without any present text."
							}
						]
					},
					{
						"text": "Statement number 2",
						"condition": 1,
						"press": [{
								"text": "Nothing much to say..."
							},
							{
								"text": "But here's an item!"
							},
							{
								"add item": {
									"name": "Some Item",
									"desc": "Something to present if you want to leave the loop"
								}
							}
						]
					}, {
						"text": "Statement number 3",
						"press": [{
							"text": "If you present Some Item here, you win!"
						}],
						"present Some Item": [{
								"text": "Hip hip hurrah"
							},
							{
								"cmd": "exit"
							}
						]
					}
				]
			}
		},
		{
			"text": "You broke out of the loop! Congrats"
		},
		{
			"text": "That's the end of it now."
		}
	]
}
```



### YAML version

It may be easier to write these in YAML instead and [convert it to json](https://www.json2yaml.com/).

```yaml
---
inventory:
- name: report
  type: 'Type: Documents <br> Received from a shady officer on an unnamed street corner.'
  desc: a report on the body
story:
- bg: background_image.png
  bgm: looping_background_music.mp3
  sfx: sound_effect_that_plays_once.mp3
  name: Name of the guy who's talking
  image: Their sprite picture
  text: The contents of their speech
  overlay: An image that shows up over them
  shout: An image that shows up over the overlay
  add item:
    name: the usual
    image: the usual
  remove item:
  - one
  - or
  - many item names
- text: another block, but bg, bgm, name, image, and overlay persist to here so I
    can just type out some dialogue. Clear those out by setting them to an empty string.
- testimony:
    default present:
    - name: A disapproving judge
      text: A block that shows up when you present an invalid item. All the normal
        rules apply
    afterword:
    - text: What the attorneys say after the guy has given his testimony
    short afterword:
    - text: A summary of the above so the player doesn't have to keep pressing buttons
    statements:
    - text: Statement number 1
      press:
      - text: These show up when you press statement number 1
      - text: and can be as long as you want
      present item1:
      - text: This shows up only when the player presents the item named item1 here.
      - text: You can have a statement block without any present text.
    - text: Statement number 2
      condition: 1
      press:
      - text: Nothing much to say...
      - text: But here's an item!
      - add item:
          name: Some Item
          desc: Something to present if you want to leave the loop
    - text: Statement number 3
      press:
      - text: If you present Some Item here, you win!
      present Some Item:
      - text: Hip hip hurrah
      - cmd: exit
- text: You broke out of the loop! Congrats
- text: That's the end of it now.

```

