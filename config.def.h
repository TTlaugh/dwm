/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define BROWSER "chromium"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "JoyPixels:pixelsize=12:antialias=true:autohint=true" };
static const char col_gray1[]       = "#1a1b26"; // #111111
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#777c99"; // #eeeeee
static const char col_gray4[]       = "#0f0f14"; // #333333
static const char col_cyan[]        = "#7aa2f7"; // #1793d1
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "a", "s", "d", "f", "q", "w", "e", "r" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Signal",   NULL,       NULL,       1 << 4,       1,           -1 },
	{ "Alacritty","floatterm",NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include <X11/XF86keysym.h>
#include "shiftview.c"
#include "movestack.c"
#include "bstack.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *run_cmd[] = { "dmenu_run"        , "-l", "10", "-x", "0", "-y", "0", "-z", "308", "-p", "cmd", NULL };
static const char *run_app[] = { "dmenu_run_desktop", "-l", "10", "-x", "0", "-y", "0", "-z", "308", "-p", "app", NULL };
static const char *quitdwm[] = { "pkill", "dwm", NULL };

static const Key keys[] = {
	/*                              key              tag */
	TAGKEYS(                        XK_a,            0)
	TAGKEYS(                        XK_s,            1)
	TAGKEYS(                        XK_d,            2)
	TAGKEYS(                        XK_f,            3)
	TAGKEYS(                        XK_q,            4)
	TAGKEYS(                        XK_w,            5)
	TAGKEYS(                        XK_e,            6)
	TAGKEYS(                        XK_r,            7)
	// TAGKEYS(                        XK_9,            8)

	/* modifier                     key              function           argument */
	{ MODKEY,                       XK_Return,       spawn,             {.v = (const char*[]){ TERMINAL, NULL } } },
	{ MODKEY,                       XK_o,            spawn,             {.v = run_cmd } },
	{ MODKEY|ShiftMask,             XK_o,            spawn,             {.v = run_app } },
	{ MODKEY|ShiftMask,             XK_Return,       spawn,             {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ControlMask,           XK_Escape,       spawn,             {.v = (const char*[]){ "dmsysact", NULL } } },

	{ MODKEY,                       XK_Escape,       spawn,             {.v = (const char*[]){ "slock", NULL } } },

	{ MODKEY,                       XK_minus,        spawn,	            SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -s 34 $(pidof -x dwmbar)") },
	{ MODKEY,                       XK_equal,        spawn,             SHCMD("wpctl set-volume -l 1 @DEFAULT_AUDIO_SINK@ 5%+; kill -s 34 $(pidof -x dwmbar)") },
	{ MODKEY,                       XK_0,            spawn,             SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -s 34 $(pidof -x dwmbar)") },

	{ MODKEY,                       XK_BackSpace,    spawn,             {.v = (const char*[]){ "dunstctl", "close", NULL } } },
	{ MODKEY|ShiftMask,             XK_BackSpace,    spawn,             {.v = (const char*[]){ "dunstctl", "close-all", NULL } } },
	{ MODKEY,                       XK_backslash,    spawn,             {.v = (const char*[]){ "dunstctl", "history-pop", NULL } } },

	{ MODKEY|ShiftMask,             XK_n,            spawn,             {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
	{ MODKEY,                       XK_F12,          spawn,             {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ MODKEY|ShiftMask,             XK_b,            spawn,             {.v = (const char*[]){ TERMINAL, "--class", "Alacritty,floatterm", "-e", "bc", "-lq", NULL } } },
	{ MODKEY|ShiftMask,             XK_t,            spawn,             {.v = (const char*[]){ TERMINAL, "-e", "trans", "-shell", "-brief", ":vi", NULL } } },
	{ MODKEY,                       XK_t,            spawn,             {.v = (const char*[]){ "dmtodo", NULL } } },
	{ MODKEY|ShiftMask,             XK_m,            spawn,             SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY|ShiftMask,             XK_p,            spawn,             SHCMD(TERMINAL " -e pulsemixer; kill -s 34 $(pidof -x dwmbar)") },
	{ MODKEY,                       XK_p,            spawn,             {.v = (const char*[]){ "passmenu", NULL } } },
	{ MODKEY,                       XK_Delete,       spawn,             {.v = (const char*[]){ "dmkill", NULL } } },
	{ MODKEY,                       XK_Home,         spawn,             {.v = (const char*[]){ "displayselect", NULL } } },

	{ 0,                            XK_Print,        spawn,             {.v = (const char*[]){ "screenshot", NULL } } },
	{ ShiftMask,                    XK_Print,        spawn,             {.v = (const char*[]){ "screenshot", "selected", NULL } } },

	{ MODKEY,                       XK_b,            togglebar,         {0} },
	{ MODKEY,                       XK_1,            setlayout,         {.v = &layouts[0]} },
	{ MODKEY,                       XK_2,            setlayout,         {.v = &layouts[1]} },
	{ MODKEY,                       XK_3,            setlayout,         {.v = &layouts[2]} },
	{ MODKEY,                       XK_4,            setlayout,         {.v = &layouts[3]} },

	{ MODKEY|ShiftMask,             XK_c,            killclient,        {0} },

	/* Mod+Ctrl+ r(eload) / q(uit) */
	{ MODKEY|ControlMask,           XK_r,            quit,              {0} },
	{ MODKEY|ControlMask,           XK_c,            spawn,             {.v = quitdwm } },

	{ MODKEY,                       XK_g,            shiftview,         {.i = -1 } },
	{ MODKEY,                       XK_semicolon,    shiftview,         {.i = +1 } },
	{ MODKEY,                       XK_j,            focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,            focusstack,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,            movestack,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,            movestack,         {.i = -1 } },
	{ MODKEY,                       XK_h,            setmfact,          {.f = -0.05} },
	{ MODKEY,                       XK_l,            setmfact,          {.f = +0.05} },

	{ MODKEY,                       XK_comma,        focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,       focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,        tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,       tagmon,            {.i = +1 } },

	{ MODKEY,                       XK_bracketright, incnmaster,        {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,  incnmaster,        {.i = -1 } },
	{ MODKEY,                       XK_space,        zoom,              {0} },
	{ MODKEY|ShiftMask,             XK_space,        togglefloating,    {0} },
	{ MODKEY,                       XK_F11,          togglefullscr,     {0} },
	{ MODKEY,                       XK_v,            togglesticky,      {0} },

	{ MODKEY|ShiftMask,             XK_x,            scratchpad_show,   {0} },
	{ MODKEY,                       XK_x,            scratchpad_hide,   {0} },
	{ MODKEY|ControlMask,           XK_x,            scratchpad_remove, {0} },

	{ MODKEY,                       XK_Tab,          view,              {0} },
	{ MODKEY,                       XK_apostrophe,   view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_apostrophe,   tag,               {.ui = ~0 } },

	{ 0, XF86XK_AudioMute,          spawn,           SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -s 34 $(pidof -x dwmbar)") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume -l 1 @DEFAULT_AUDIO_SINK@ 5%+; kill -s 34 $(pidof -x dwmbar)") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -s 34 $(pidof -x dwmbar)") },
	// { 0, XF86XK_AudioPrev,          spawn,           {.v = (const char*[]){ "mpc", "prev", NULL } } },
	// { 0, XF86XK_AudioNext,          spawn,           {.v = (const char*[]){ "mpc",  "next", NULL } } },
	// { 0, XF86XK_AudioPause,         spawn,           {.v = (const char*[]){ "mpc", "pause", NULL } } },
	// { 0, XF86XK_AudioPlay,          spawn,           {.v = (const char*[]){ "mpc", "play", NULL } } },
	// { 0, XF86XK_AudioStop,          spawn,           {.v = (const char*[]){ "mpc", "stop", NULL } } },
	// { 0, XF86XK_AudioRewind,        spawn,           {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	// { 0, XF86XK_AudioForward,       spawn,           {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	// { 0, XF86XK_AudioMedia,         spawn,           {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ 0, XF86XK_AudioMicMute,       spawn,           SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	// { 0, XF86XK_sysactOff,           spawn,          {.v = (const char*[]){ "dmsysact", NULL } } },
	{ 0, XF86XK_Calculator,         spawn,           {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,              spawn,           {.v = (const char*[]){ "systemctl", "suspend", NULL } } },
	{ 0, XF86XK_WWW,                spawn,           {.v = (const char*[]){ BROWSER, NULL } } },
	{ 0, XF86XK_DOS,                spawn,           {.v = (const char*[]){ TERMINAL, NULL } } },
	{ 0, XF86XK_ScreenSaver,        spawn,           SHCMD("slock & xset dpms force off") },
	{ 0, XF86XK_TaskPane,           spawn,           {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	// { 0, XF86XK_Mail,               spawn,           SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,         spawn,           {.v = (const char*[]){ TERMINAL, "-e",  "vifm",  "/", NULL } } },
	// { 0, XF86XK_Battery,            spawn,           SHCMD("") },
	{ 0, XF86XK_Launch1,            spawn,           {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,     spawn,           {.v = (const char*[]){ "toggletouchpad", NULL } } },
	{ 0, XF86XK_TouchpadOff,        spawn,           {.v = (const char*[]){ "toggletouchpad", "disable", NULL } } },
	{ 0, XF86XK_TouchpadOn,         spawn,           {.v = (const char*[]){ "toggletouchpad", "enable", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,    spawn,           SHCMD("xbacklight -inc 10; kill -s 35 $(pidof -x dwmbar)") },
	{ 0, XF86XK_MonBrightnessDown,  spawn,           SHCMD("xbacklight -dec 10; kill -s 35 $(pidof -x dwmbar)") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[3]} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,      { .i = -1 } },
	{ ClkTagBar,            0,              Button5,        shiftview,      { .i = +1 } },

	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button2,        killclient,     {.i = +1 } },
	{ ClkWinTitle,          0,              Button3,        togglesticky,   {.i = -1 } },

	{ ClkStatusText,        0,              Button3,        spawn,          {.v = (const char*[]){ "dmsysact", NULL } } },

	{ ClkRootWin,           0,              Button1,        spawn,          {.v = (const char*[]){ "pkill", "dmenu", NULL } } },
	{ ClkRootWin,           0,              Button2,        togglebar,      {0} },
	{ ClkRootWin,           0,              Button3,        spawn,          {.v = run_cmd } },
	{ ClkRootWin,           MODKEY,         Button3,        spawn,          {.v = (const char*[]){ TERMINAL, NULL } } },
};

