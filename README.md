# cli-menu

## Usage
```cpp
// C++

Menu title_screen
(
    "play,"
    "settings:"
        "gameplay,"
        "video:"
            "resolution,"
            "fullscreen:"
                "on,"
                "off;;"
        "audio:"
            "music,"
            "effects;;"
    "credits,"
    "quit"
);

title_screen.render();
```

## Output
![Output](https://i.imgur.com/HGSwiRu.gif "Output")
