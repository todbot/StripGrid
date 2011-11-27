//
// Logos.h --
//
//

#define cw  {255,255,255}
#define cr  {255,  0,  0}
#define cg  {  0,255,  0}
#define cb  {  0,  0,255}
#define co  {  0,  0,  0}


const PROGMEM color_t logo0[rows*cols] =
{
  cr, cr, cr, cr, cr, cr, 
  cw, co, co, co, co, cw, 
  cw, co, cg, cg, co, cw, 
  cw, co, co, co, co, cw, 
  cb, cb, cb, cb, cb, cb, 
};

const PROGMEM color_t logo1[rows*cols] =
{
  co, co, co, co, co, co, 
  co, co, co, co, co, co, 
  co, co, co, co, co, co, 
  co, co, co, co, co, co, 
  co, co, co, co, co, co, 
};


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
    { cr, cr, cr, cr, cr, cr, },
    { cw, co, co, co, co, cw, },
    { cw, co, cg, cg, co, cw, },
    { cw, co, co, co, co, cw, },
    { cb, cb, cb, cb, cb, cb, },
};
*/
 /*
// this also works, but without ptrs gives "section error"
const PROGMEM color_t cw = {255,255,255};
const PROGMEM color_t cr = {255,  0,  0};
const PROGMEM color_t cg = {  0,255,  0};
const PROGMEM color_t cb = {  0,  0,255};
const PROGMEM color_t co = {  0,  0,  0};

const PROGMEM color_t* logoTod[rows][cols] =
{
    { &cr, &cr, &cr, &cr, &cr, &cr, },
    { &cr, &co, &co, &co, &co, &cr, },
    { &cr, &co, &cg, &cg, &co, &cr, },
    { &cr, &co, &co, &co, &co, &cr, },
    { &cb, &cb, &cb, &cb, &cb, &cb, },
};
*/
