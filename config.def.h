/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "alacritty"
#define BROWSER "chromium"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack Nerd Font:size=12" };
static const char col_gray1[]       = "#111111";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#eeeeee";
static const char col_gray4[]       = "#333333";
static const char col_cyan[]        = "#1793d1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "a", "s", "d", "f", "1", "2", "3", "4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
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
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *browsercmd[]  = { BROWSER, NULL };
static const char *dmenuruncmd[]  = { "dmenu_run", "-p", "Run:", NULL };
static const char *dmpowercmd[]  = { "dmpower", NULL };

#include <X11/XF86keysym.h>
#include "nextprevtag.c"
#include "movestack.c"

static const Key keys[] = {
	/* modifier                     key              function           argument */
	{ MODKEY,                       XK_Return,       spawn,             {.v = termcmd } },
	{ MODKEY,                       XK_o,            spawn,             {.v = dmenuruncmd } },
	{ MODKEY|ShiftMask,             XK_Return,       spawn,             {.v = browsercmd } },
	{ MODKEY|ControlMask,           XK_Escape,       spawn,             {.v = dmpowercmd } },

	{ MODKEY,                       XK_Escape,       spawn,             {.v = (const char*[]){ "slock", NULL } } },

	{ MODKEY,                       XK_minus,        spawn,	            SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -s 34 $(cat ~/.cache/pidofbar)") },
	{ MODKEY,                       XK_equal,        spawn,             SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -s 34 $(cat ~/.cache/pidofbar)") },
	{ MODKEY|ShiftMask,             XK_m,            spawn,             SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -s 34 $(cat ~/.cache/pidofbar)") },

	{ MODKEY,                       XK_BackSpace,    spawn,             SHCMD("dunstctl close") },
	{ MODKEY|ShiftMask,             XK_BackSpace,    spawn,             SHCMD("dunstctl close-all") },
	{ MODKEY,                       XK_backslash,    spawn,             SHCMD("dunstctl history-pop") },

	{ MODKEY|ShiftMask,             XK_w,            spawn,             {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
	{ MODKEY|ShiftMask,             XK_p,            spawn,             SHCMD(TERMINAL " -e pulsemixer; kill -s 34 $(cat ~/.cache/pidofbar)") },

	{ 0,                            XK_Print,        spawn,             {.v = (const char*[]){ "screenshot", NULL } } },
	{ ShiftMask,                    XK_Print,        spawn,             {.v = (const char*[]){ "screenshot", "selected", NULL } } },

	{ MODKEY,                       XK_b,            togglebar,         {0} },
	{ MODKEY,                       XK_q,            setlayout,         {.v = &layouts[0]} },
	{ MODKEY,                       XK_w,            setlayout,         {.v = &layouts[1]} },
	{ MODKEY,                       XK_e,            setlayout,         {.v = &layouts[2]} },

	{ MODKEY|ShiftMask,             XK_q,            killclient,        {0} },

	{ MODKEY|ControlMask,           XK_q,            quit,              {0} },

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
	{ MODKEY|ControlMask,           XK_f,            togglefullscr,     {0} },
	{ MODKEY,                       XK_v,            togglesticky,      {0} },

	{ MODKEY,                       XK_z,            scratchpad_show,   {0} },
	{ MODKEY|ShiftMask,             XK_x,            scratchpad_hide,   {0} },
	{ MODKEY,                       XK_c,            scratchpad_remove, {0} },

	// { MODKEY,                       XK_u,            view,              {0} },
	{ MODKEY,                       XK_0,            view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,               {.ui = ~0 } },

	{ MODKEY,                       XK_Tab,          view_adjacent,     { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,          view_adjacent,     { .i = -1 } },

	TAGKEYS(                        XK_a,            0)
	TAGKEYS(                        XK_s,            1)
	TAGKEYS(                        XK_d,            2)
	TAGKEYS(                        XK_f,            3)
	TAGKEYS(                        XK_1,            4)
	TAGKEYS(                        XK_2,            5)
	TAGKEYS(                        XK_3,            6)
	TAGKEYS(                        XK_4,            7)
	// TAGKEYS(                        XK_9,            8)

	{ 0, XF86XK_AudioMute,          spawn,           SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -s 34 $(cat ~/.cache/pidofbar)") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -s 34 $(cat ~/.cache/pidofbar)") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,           SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -s 34 $(cat ~/.cache/pidofbar)") },
	// { 0, XF86XK_AudioPrev,          spawn,           {.v = (const char*[]){ "mpc", "prev", NULL } } },
	// { 0, XF86XK_AudioNext,          spawn,           {.v = (const char*[]){ "mpc",  "next", NULL } } },
	// { 0, XF86XK_AudioPause,         spawn,           {.v = (const char*[]){ "mpc", "pause", NULL } } },
	// { 0, XF86XK_AudioPlay,          spawn,           {.v = (const char*[]){ "mpc", "play", NULL } } },
	// { 0, XF86XK_AudioStop,          spawn,           {.v = (const char*[]){ "mpc", "stop", NULL } } },
	// { 0, XF86XK_AudioRewind,        spawn,           {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	// { 0, XF86XK_AudioForward,       spawn,           {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	// { 0, XF86XK_AudioMedia,         spawn,           {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	{ 0, XF86XK_AudioMicMute,       spawn,           SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,           spawn,           {.v = dmpowercmd } },
	{ 0, XF86XK_Calculator,         spawn,           {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,              spawn,           {.v = (const char*[]){ "systemctl", "suspend", NULL } } },
	{ 0, XF86XK_WWW,                spawn,           {.v = (const char*[]){ BROWSER, NULL } } },
	{ 0, XF86XK_DOS,                spawn,           {.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,        spawn,           SHCMD("slock & xset dpms force off") },
	{ 0, XF86XK_TaskPane,           spawn,           {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	// { 0, XF86XK_Mail,               spawn,           SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,         spawn,           {.v = (const char*[]){ TERMINAL, "-e",  "vifm",  "/", NULL } } },
	// { 0, XF86XK_Battery,            spawn,           SHCMD("") },
	{ 0, XF86XK_Launch1,            spawn,           {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,     spawn,           {.v = (const char*[]){ "toggletouchpad", NULL } } },
	{ 0, XF86XK_TouchpadOff,        spawn,           {.v = (const char*[]){ "toggletouchpad", "disable", NULL } } },
	{ 0, XF86XK_TouchpadOn,         spawn,           {.v = (const char*[]){ "toggletouchpad", "enable", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,    spawn,           {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,  spawn,           {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[1]} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        view_adjacent,  { .i = -1 } },
	{ ClkTagBar,            0,              Button5,        view_adjacent,  { .i = +1 } },

	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,          MODKEY,         Button1,        incnmaster,     {.i = +1 } },
	{ ClkWinTitle,          MODKEY,         Button3,        incnmaster,     {.i = -1 } },

	{ ClkStatusText,        0,              Button2,        spawn,          {.v = dmpowercmd } },
	// { ClkStatusText,        0,              Button3,        spawn,          {.v = statusdashboard } },

	{ ClkRootWin,           0,              Button2,        togglebar,      {0} },
	{ ClkRootWin,           0,              Button3,        spawn,          {.v = dmenuruncmd } },
	{ ClkRootWin,           MODKEY,         Button3,        spawn,          {.v = termcmd } },
};

