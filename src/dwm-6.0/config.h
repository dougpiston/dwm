/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[] = "-*-ohsnap.icons-medium-*-normal--12-87-100-100-c-70-iso8859-1";
#define NUMCOLORS 13
static const char colors[NUMCOLORS][ColLast][9] = {
  // border foreground background
  { "#5f636d", "#5f636d", "#1d1f21" }, // 1 = normal (grey on black)
  { "#f0c674", "#c5c8c6", "#1d1f21" }, // 2 = selected (white on black)
  { "#dc322f", "#cc6666", "#1d1f21" }, // 3 = urgent (black on gray)
  { "#717782", "#717782", "#1d1f21" }, // 4 = darkgrey on black (triangle)
  { "#282a2e", "#1d1f21", "#282a2e" }, // 5 = black on darkgrey (triangle)
  { "#282a2e", "#b294bb", "#282a2e" }, // 6 = magenta on darkgrey
  { "#282a2e", "#cc6666", "#1d1f21" }, // 7 = red on black
  { "#282a2e", "#b5bd68", "#1d1f21" }, // 8 = green on black
  { "#282a2e", "#81a2be", "#1d1f21" }, // 9 = blue on darkgrey
  { "#282a2e", "#f0c674", "#1d1f21" }, // A = yellow on black
  { "#282a2e", "#f0c674", "#282a2e" }, // B = yellow on darkgrey
  { "#282a2e", "#de935f", "#1d1f21" }, // C = orange on black
  { "#282a2e", "#8abeb7", "#282a2e" }, // D = cyan on darkgrey
};
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 8; /* snap pixel */
static const Bool showbar = True; /* False means no bar */
static const Bool topbar = True; /* False means bottom bar */

/* tagging */
static const char *tags[] = { "Irssi", "iNet", "File", "eMail", "rTor"};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	{ "Firefox",  NULL,       NULL,       1 << 1,       False,       -1 },
  { NULL,       NULL,       "rtorrent", 1 << 4,       False,       -1 },
  { "Pcmanfm",  NULL,       NULL,       1 << 2,       False,       -1 },
  { NULL,       NULL,       "mutt",     1 << 3,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
  { "[õ]",      bstack }, /* first entry is default */
	{ "[þ]",      tile },
	{ "[ý]",      NULL },    /* no layout function means floating behavior */
	{ "M",      monocle },
	{ "[û]",      bstackhoriz },
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
static const char *dmenucmd[]      = { "dmenu_run", "-fn", font, "-nb", colors[0][ColBG], "-nf", colors[0][ColFG], "-sb", colors[1][ColBG], "-sf", colors[1][ColFG], NULL };
static const char *termcmd[]       = { "urxvt", NULL };
static const char *pcmancmd[]      = { "pcmanfm", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "urxvt", "-name", scratchpadname, "-geometry", "100x25", NULL };
static const char *rtorrentcmd[]   = { "urxvt", "-title", "rtorrent", "-e", "rtorrent", NULL };
static const char *muttcmd[]       = { "urxvt", "-title", "mutt", "-e", "mutt", NULL };
static const char *irssicmd[]      = { "urxvt", "-e", "irssi", NULL };
static const char *volupcmd[]      = { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *voldncmd[]      = { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *mpdstop[]       = { "ncmpcpp", "stop", NULL };
static const char *mpdprev[]       = { "ncmpcpp", "prev", NULL };
static const char *mpdnext[]       = { "ncmpcpp", "next", NULL };
static const char *firefox[]       = { "firefox", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
  { 0,                          0x1008ff13,  spawn,          {.v = volupcmd } },
  { 0,                          0x1008ff11,  spawn,          {.v = voldncmd } },
  { MODKEY,                       XK_s,      spawn,          {.v = mpdstop } },
  { MODKEY,                       XK_p,      spawn,          {.v = mpdprev } },
  { MODKEY,                       XK_n,      spawn,          {.v = mpdnext } },
  { MODKEY,                       XK_v,      spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_x,      spawn,          {.v = firefox } },
  { MODKEY,                       XK_z,      togglescratch,  {.v = scratchpadcmd} },
  { MODKEY,                       XK_a,      spawn,          {.v = pcmancmd} },
  { MODKEY,                       XK_r,      spawn,          {.v = rtorrentcmd} },
  { MODKEY,                       XK_i,      spawn,          {.v = irssicmd} },
  { MODKEY,                       XK_m,      spawn,          {.v = muttcmd} },
  { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_w,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
  { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_o,      setlayout,      {.v = &layouts[3]} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

