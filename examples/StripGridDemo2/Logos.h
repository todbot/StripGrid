//
// Logos.h --
//
//



#define cw  {255,255,255}
#define cR  {255,  0,  0}
#define cG  {  0,255,  0}
#define cB  {  0,  0,255}
#define cC  {  0,255,255}
#define cP  {255,  0,255}
#define co  {  0,  0,  0}


// test img
const PROGMEM color_t logo0[rows*cols] =
{
  cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, 
  cw, co, co, co, co, co, co, co, co, co, co, co, co, co, co, cw, 
  cw, co, co, co, co, co, co, cw, cw, co, co, co, co, co, co, cw, 
  cP, co, co, co, co, co, co, cG, cG, co, co, co, co, co, co, cC, 
  cP, co, co, co, co, co, cw, cR, cR, cw, co, co, co, co, co, cC, 
  cP, co, co, co, co, co, cw, cG, cG, cw, co, co, co, co, co, cC, 
  cP, co, co, co, co, co, co, cG, cG, co, co, co, co, co, co, cC, 
  cw, co, co, co, co, co, cR, cR, cR, cR, co, co, co, co, co, cw, 
  cw, co, co, co, co, co, co, co, co, co, co, co, co, co, co, cw, 
  cB, cB, cB, cB, cB, cB, cB, cB, cB, cB, cB, cB, cB, cB, cB, cB, 
};

// crashspace logo, sort of
const PROGMEM color_t logo1[rows*cols] =
{
  co, co, co, co, co, co, cR, co, co, co, co, co, co,  co, cR, cR, 
  co, co, co, co, co, cR, co, cR, co, co, co, co, co,  co, cR, co, 
  co, co, co, co, cR, cR, cR, cR, cR, co, co, co, co,  co, cR, cR, 
  co, co, co, cR, cR, co, cR, co, cR, cR, co, co, co,  co, co, co, 
  co, co, cR, cR, co, co, cR, co, co, cR, cR, co, co,  co, cR, cR, 
  co, cR, cR, co, co, co, co, cR, co, co, cR, cR, co,  co, cR, co, 
  co, cR, co, co, co, co, co, cR, co, co, co, cR, co,  co, co, cR, 
  cR, cR, co, co, co, cR, cR, co, co, co, co, cR, cR,  co, cR, cR, 
  cR, cR, co, co, co, co, cR, co, co, co, co, cR, cR,  co, co, co, 
  cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR, cR,  co, co, co, 
} ;


// list of all the logos
const PROGMEM color_t* logoList[] = 
{
  logo0,
  logo1,
};








// -- old stuff, don't use --

/*
const PROGMEM color_t logo0[rows][cols] =
{
    { cR, cR, cR, cR, cR, cR, },
    { cw, co, co, co, co, cw, },
    { cw, co, cG, cG, co, cw, },
    { cw, co, co, co, co, cw, },
    { cB, cB, cB, cB, cB, cB, },
};
*/
 /*
// this also works, but without ptrs gives "section error"
const PROGMEM color_t cw = {255,255,255};
const PROGMEM color_t cR = {255,  0,  0};
const PROGMEM color_t cG = {  0,255,  0};
const PROGMEM color_t cB = {  0,  0,255};
const PROGMEM color_t co = {  0,  0,  0};

const PROGMEM color_t* logoTod[rows][cols] =
{
    { &cR, &cR, &cR, &cR, &cR, &cR, },
    { &cR, &co, &co, &co, &co, &cR, },
    { &cR, &co, &cG, &cG, &co, &cR, },
    { &cR, &co, &co, &co, &co, &cR, },
    { &cB, &cB, &cB, &cB, &cB, &cB, },
};
*/
