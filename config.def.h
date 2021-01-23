static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#e69900";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class, instance, title, tags mask, isfloating, isterminal, noswallow, monitor */
	{ "Gimp",                                    NULL, NULL,          1 << 6, 1, 0, 0, -1 },
	{ "Firefox",                                 NULL, NULL,          1 << 1, 0, 0, 0, -1 },
	{ "okular",                                  NULL, NULL,          1 << 2, 0, 0, 0, -1 },
	{ "Spotify",                                 NULL, NULL,          1 << 3, 0, 0, 0, -1 },
	{ "com-st-microxplorer-maingui-STM32CubeMX", NULL, NULL,          1 << 4, 1, 0, 0, -1 },
	{ "Eclipse",                                 NULL, NULL,          1 << 5, 0, 0, 0, -1 },
    { "St",                                      NULL, NULL,          0,      0, 1, 0, -1 },
    { "Alacritty",                               NULL, NULL,          0,      0, 1, 0, -1 },
    { NULL,                                      NULL, "Event Tester",0,      0, 1, 1, -1 }, 
};

static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_h,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY,                       XK_equal,  spawn,          SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_minus,  spawn,          SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") }, 
    { MODKEY|ShiftMask,             XK_equal,  spawn,          SHCMD("cd /home/evn/.scripts/brightness_control; ./brightness_increase") },
    { MODKEY|ShiftMask,             XK_minus,  spawn,          SHCMD("cd /home/evn/.scripts/brightness_control; ./brightness_decrease") }, 
    { MODKEY,                       XK_m,      spawn,          SHCMD("pamixer -m; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("pamixer -u; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                       XK_w,      spawn,          SHCMD("$BROWSER") },
    { MODKEY,                       XK_t,      spawn,          SHCMD("st -e fish") },
    { MODKEY,                       XK_b,      spawn,          SHCMD("st -e bashtop") },
    { MODKEY,                       XK_n,      spawn,          SHCMD("st -e newsboat") },
    { MODKEY,                       XK_c,      spawn,          SHCMD("st -e cmus") },
    { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("slock") },
    { MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("st vim /home/evn/Projects/dwm/config.def.h") },
    { MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("st vim /home/evn/.vimrc") },
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

static Button buttons[] = {
	/* click                event mask      button          function        argument */ 
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
