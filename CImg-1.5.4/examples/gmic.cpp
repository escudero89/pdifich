/*
 #
 #  File        : gmic.cpp
 #                ( C++ source file )
 #
 #  Description : GREYC's Magic Image Converter - G'MIC Language interpreter
 #                ( http://gmic.sourceforge.net )
 #                This file is also a part of the CImg Library project.
 #                ( http://cimg.sourceforge.net )
 #
 #  Copyright   : David Tschumperle
 #                ( http://tschumperle.users.greyc.fr/ )
 #
 #  License     : CeCILL v2.0
 #                ( http://www.cecill.info/licences/Licence_CeCILL_V2-en.html )
 #
 #  This software is governed by the CeCILL  license under French law and
 #  abiding by the rules of distribution of free software.  You can  use,
 #  modify and/ or redistribute the software under the terms of the CeCILL
 #  license as circulated by CEA, CNRS and INRIA at the following URL
 #  "http://www.cecill.info".
 #
 #  As a counterpart to the access to the source code and  rights to copy,
 #  modify and redistribute granted by the license, users are provided only
 #  with a limited warranty  and the software's author,  the holder of the
 #  economic rights,  and the successive licensors  have only  limited
 #  liability.
 #
 #  In this respect, the user's attention is drawn to the risks associated
 #  with loading,  using,  modifying and/or developing or reproducing the
 #  software by the user in light of its specific status of free software,
 #  that may mean  that it is complicated to manipulate,  and  that  also
 #  therefore means  that it is reserved for developers  and  experienced
 #  professionals having in-depth computer knowledge. Users are therefore
 #  encouraged to load and test the software's suitability as regards their
 #  requirements in conditions enabling the security of their systems and/or
 #  data to be ensured and,  more generally, to use and operate it in the
 #  same conditions as regards security.
 #
 #  The fact that you are presently reading this means that you have had
 #  knowledge of the CeCILL license and that you accept its terms.
 #
*/

// Add G'MIC-specific methods to the CImg library.
//-------------------------------------------------
#ifdef cimg_plugin

template<typename t>
CImg<T>& operator_eq(const t val) {
  cimg_for(*this,ptrd,T) *ptrd = (T)(*ptrd == (T)val);
  return *this;
}

CImg<T>& operator_eq(const char *const expression) {
  const unsigned int omode = cimg::exception_mode();
  cimg::exception_mode() = 0;
  try {
    const CImg<T> _base = std::strstr(expression,"i(")?+*this:CImg<T>(), &base = _base?_base:*this;
    _cimg_math_parser mp(base,expression,"operator_eq");
    T *ptrd = _data;
    cimg_forXYZC(*this,x,y,z,c) { *ptrd = (T)(*ptrd == (T)mp.eval(x,y,z,c)); ++ptrd; }
  } catch (CImgException&) {
    cimg::exception_mode() = omode;
    CImg<T> values(_width,_height,_depth,_spectrum);
    values = expression;
    operator_eq(values);
  }
  cimg::exception_mode() = omode;
  return *this;
}

template<typename t>
CImg<T>& operator_eq(const CImg<t>& img) {
  const unsigned long siz = size(), isiz = img.size();
  if (siz && isiz) {
    if (is_overlapped(img)) return operator_eq(+img);
    T *ptrd = _data, *const ptre = _data + siz;
    if (siz>isiz)
      for (unsigned long n = siz/isiz; n; --n)
        for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
          *ptrd = (T)(*ptrd == (T)*(ptrs++));
    for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd == (T)*(ptrs++));
  }
  return *this;
}

template<typename t>
CImg<T>& operator_neq(const t val) {
  cimg_for(*this,ptrd,T) *ptrd = (T)(*ptrd != (T)val);
  return *this;
}

CImg<T>& operator_neq(const char *const expression) {
  const unsigned int omode = cimg::exception_mode();
  cimg::exception_mode() = 0;
  try {
    const CImg<T> _base = std::strstr(expression,"i(")?+*this:CImg<T>(), &base = _base?_base:*this;
    _cimg_math_parser mp(base,expression,"operator_neq");
    T *ptrd = _data;
    cimg_forXYZC(*this,x,y,z,c) { *ptrd = (T)(*ptrd != (T)mp.eval(x,y,z,c)); ++ptrd; }
  } catch (CImgException&) {
    cimg::exception_mode() = omode;
    CImg<T> values(_width,_height,_depth,_spectrum);
    values = expression;
    operator_neq(values);
  }
  cimg::exception_mode() = omode;
  return *this;
}

template<typename t>
CImg<T>& operator_neq(const CImg<t>& img) {
  const unsigned long siz = size(), isiz = img.size();
  if (siz && isiz) {
    if (is_overlapped(img)) return operator_neq(+img);
    T *ptrd = _data, *const ptre = _data + siz;
    if (siz>isiz)
      for (unsigned long n = siz/isiz; n; --n)
        for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
          *ptrd = (T)(*ptrd != (T)*(ptrs++));
    for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd != (T)*(ptrs++));
  }
  return *this;
}

template<typename t>
CImg<T>& operator_gt(const t val) {
  cimg_for(*this,ptrd,T) *ptrd = (T)(*ptrd > (T)val);
  return *this;
}

CImg<T>& operator_gt(const char *const expression) {
  const unsigned int omode = cimg::exception_mode();
  cimg::exception_mode() = 0;
  try {
    const CImg<T> _base = std::strstr(expression,"i(")?+*this:CImg<T>(), &base = _base?_base:*this;
    _cimg_math_parser mp(base,expression,"operator_gt");
    T *ptrd = _data;
    cimg_forXYZC(*this,x,y,z,c) { *ptrd = (T)(*ptrd > (T)mp.eval(x,y,z,c)); ++ptrd; }
  } catch (CImgException&) {
    cimg::exception_mode() = omode;
    CImg<T> values(_width,_height,_depth,_spectrum);
    values = expression;
    operator_gt(values);
  }
  cimg::exception_mode() = omode;
  return *this;
}

template<typename t>
CImg<T>& operator_gt(const CImg<t>& img) {
  const unsigned long siz = size(), isiz = img.size();
  if (siz && isiz) {
    if (is_overlapped(img)) return operator_gt(+img);
    T *ptrd = _data, *const ptre = _data + siz;
    if (siz>isiz)
      for (unsigned long n = siz/isiz; n; --n)
        for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
          *ptrd = (T)(*ptrd > (T)*(ptrs++));
    for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd > (T)*(ptrs++));
  }
  return *this;
}

template<typename t>
CImg<T>& operator_ge(const t val) {
  cimg_for(*this,ptrd,T) *ptrd = (T)(*ptrd >= (T)val);
  return *this;
}

CImg<T>& operator_ge(const char *const expression) {
  const unsigned int omode = cimg::exception_mode();
  cimg::exception_mode() = 0;
  try {
    const CImg<T> _base = std::strstr(expression,"i(")?+*this:CImg<T>(), &base = _base?_base:*this;
    _cimg_math_parser mp(base,expression,"operator_ge");
    T *ptrd = _data;
    cimg_forXYZC(*this,x,y,z,c) { *ptrd = (T)(*ptrd >= (T)mp.eval(x,y,z,c)); ++ptrd; }
  } catch (CImgException&) {
    cimg::exception_mode() = omode;
    CImg<T> values(_width,_height,_depth,_spectrum);
    values = expression;
    operator_ge(values);
  }
  cimg::exception_mode() = omode;
  return *this;
}

template<typename t>
CImg<T>& operator_ge(const CImg<t>& img) {
  const unsigned long siz = size(), isiz = img.size();
  if (siz && isiz) {
    if (is_overlapped(img)) return operator_ge(+img);
    T *ptrd = _data, *const ptre = _data + siz;
    if (siz>isiz)
      for (unsigned long n = siz/isiz; n; --n)
        for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
          *ptrd = (T)(*ptrd >= (T)*(ptrs++));
    for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd >= (T)*(ptrs++));
  }
  return *this;
}

template<typename t>
CImg<T>& operator_lt(const t val) {
  cimg_for(*this,ptrd,T) *ptrd = (T)(*ptrd < (T)val);
  return *this;
}

CImg<T>& operator_lt(const char *const expression) {
  const unsigned int omode = cimg::exception_mode();
  cimg::exception_mode() = 0;
  try {
    const CImg<T> _base = std::strstr(expression,"i(")?+*this:CImg<T>(), &base = _base?_base:*this;
    _cimg_math_parser mp(base,expression,"operator_lt");
    T *ptrd = _data;
    cimg_forXYZC(*this,x,y,z,c) { *ptrd = (T)(*ptrd < (T)mp.eval(x,y,z,c)); ++ptrd; }
  } catch (CImgException&) {
    cimg::exception_mode() = omode;
    CImg<T> values(_width,_height,_depth,_spectrum);
    values = expression;
    operator_lt(values);
  }
  cimg::exception_mode() = omode;
  return *this;
}

template<typename t>
CImg<T>& operator_lt(const CImg<t>& img) {
  const unsigned long siz = size(), isiz = img.size();
  if (siz && isiz) {
    if (is_overlapped(img)) return operator_lt(+img);
    T *ptrd = _data, *const ptre = _data + siz;
    if (siz>isiz)
      for (unsigned long n = siz/isiz; n; --n)
        for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
          *ptrd = (T)(*ptrd < (T)*(ptrs++));
    for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd < (T)*(ptrs++));
  }
  return *this;
}

template<typename t>
CImg<T>& operator_le(const t val) {
  cimg_for(*this,ptrd,T) *ptrd = (T)(*ptrd <= (T)val);
  return *this;
}

CImg<T>& operator_le(const char *const expression) {
  const unsigned int omode = cimg::exception_mode();
  cimg::exception_mode() = 0;
  try {
    const CImg<T> _base = std::strstr(expression,"i(")?+*this:CImg<T>(), &base = _base?_base:*this;
    _cimg_math_parser mp(base,expression,"operator_le");
    T *ptrd = _data;
    cimg_forXYZC(*this,x,y,z,c) { *ptrd = (T)(*ptrd <= (T)mp.eval(x,y,z,c)); ++ptrd; }
  } catch (CImgException&) {
    cimg::exception_mode() = omode;
    CImg<T> values(_width,_height,_depth,_spectrum);
    values = expression;
    operator_le(values);
  }
  cimg::exception_mode() = omode;
  return *this;
}

template<typename t>
CImg<T>& operator_le(const CImg<t>& img) {
  const unsigned long siz = size(), isiz = img.size();
  if (siz && isiz) {
    if (is_overlapped(img)) return operator_le(+img);
    T *ptrd = _data, *const ptre = _data + siz;
    if (siz>isiz)
      for (unsigned long n = siz/isiz; n; --n)
        for (const t *ptrs = img._data, *ptrs_end = ptrs + isiz; ptrs<ptrs_end; ++ptrd)
          *ptrd = (T)(*ptrd <= (T)*(ptrs++));
    for (const t *ptrs = img._data; ptrd<ptre; ++ptrd) *ptrd = (T)(*ptrd <= (T)*(ptrs++));
  }
  return *this;
}

CImg<T>& mul(const char *const expression) {
  return operator*=(expression);
}

CImg<T> get_mul(const char *const expression) const {
  return (+*this).mul(expression);
}

CImg<T>& div(const char *const expression) {
  return operator/=(expression);
}

CImg<T> get_div(const char *const expression) const {
  return (+*this).div(expression);
}

CImg<T>& gmic_rol(const float n) {
  return rol((unsigned int)n);
}

CImg<T> get_gmic_rol(const float n) const {
  return get_rol((unsigned int)n);
}

CImg<T>& gmic_ror(const float n) {
  return ror((unsigned int)n);
}

CImg<T> get_gmic_ror(const float n) const {
  return get_ror((unsigned int)n);
}

template<typename t>
CImg<T>& replace(CImg<t>& img) {
  return img.move_to(*this);
}

template<typename t>
CImg<T> get_replace(const CImg<t>& img) const {
  return +img;
}

CImg<T>& gmic_autocrop(const CImg<T>& color=CImg<T>::empty()) {
  if (color.width()==1) autocrop(*color);
  else autocrop(color);
  return *this;
}

CImg<T> get_gmic_autocrop(const CImg<T>& color=CImg<T>::empty()) {
  return (+*this).gmic_autocrop(color);
}

CImg<T> get_gmic_set(const double value,
                     const int x, const int y, const int z, const int v) const {
  return (+*this).gmic_set(value,x,y,z,v);
}

CImg<T>& gmic_set(const double value,
                  const int x, const int y, const int z, const int v) {
  (*this).atXYZC(x,y,z,v,0) = (T)value;
  return *this;
}

CImg<T> get_draw_point(const int x, const int y, const int z, const T *const col,
                       const float opacity) const {
  return (+*this).draw_point(x,y,z,col,opacity);
}

CImg<T> get_draw_line(const int x0, const int y0, const int x1, const int y1, const T *const col,
                      const float opacity, const unsigned int pattern) const {
  return (+*this).draw_line(x0,y0,x1,y1,col,opacity,pattern);
}

template<typename t>
CImg<T> get_draw_polygon(const CImg<t>& pts, const T *const col, const float opacity) const {
  return (+*this).draw_polygon(pts,col,opacity);
}

template<typename t>
CImg<T> get_draw_polygon(const CImg<t>& pts, const T *const col, const float opacity,
                         const unsigned int pattern) const {
  return (+*this).draw_polygon(pts,col,opacity,pattern);
}

CImg<T> get_draw_spline(const int x0, const int y0, const float u0, const float v0,
                        const int x1, const int y1, const float u1, const float v1,
                        const T *const color, const float opacity, const float precision,
                        const unsigned int pattern) const {
  return (+*this).draw_spline(x0,y0,u0,v0,x1,y1,u1,v1,color,opacity,precision,pattern);
}

CImg<T> get_draw_circle(const int x, const int y, const int r, const T *const col,
                        const float opacity) const {
  return (+*this).draw_circle(x,y,r,col,opacity);
}

CImg<T> get_draw_circle(const int x, const int y, const int r, const T *const col,
                        const float opacity,
                        const unsigned int pattern) const {
  return (+*this).draw_circle(x,y,r,col,opacity,pattern);
}

CImg<T> get_draw_ellipse(const int x, const int y, const float r0, const float r1,
                         const float angle, const T *const col, const float opacity) const {
  return (+*this).draw_ellipse(x,y,r0,r1,angle,col,opacity);
}

CImg<T> get_draw_ellipse(const int x, const int y, const float r0, const float r1,
                         const float angle, const T *const col, const float opacity,
                         const unsigned int pattern) const {
  return (+*this).draw_ellipse(x,y,r0,r1,angle,col,opacity,pattern);
}

CImg<T>& gmic_draw_text(const int x, const int y,
                        const char *const text, const T *const col,
                        const int bg, const float opacity, const unsigned int siz,
                        const unsigned int nb_cols) {
  if (is_empty()) {
    const T one[] = { 1 };
    assign().draw_text(x,y,"%s",one,0,opacity,siz,text).resize(-100,-100,1,nb_cols);
    cimg_forC(*this,c) get_shared_channel(c)*=col[c];
  } else draw_text(x,y,"%s",col,bg,opacity,siz,text);
  return *this;
}

CImg<T> get_gmic_draw_text(const int x, const int y,
                           const char *const text, const T *const col,
                           const int bg, const float opacity, const unsigned int siz,
                           const unsigned int nb_cols) const {
  return (+*this).gmic_draw_text(x,y,text,col,bg,opacity,siz,nb_cols);
}

CImg<T> get_draw_image(const int x, const int y, const int z, const int c,
                       const CImg<T>& sprite, const CImg<T>& mask, const float opacity,
                       const float max_opacity_mask) const {
  return (+*this).draw_image(x,y,z,c,sprite,mask,opacity,max_opacity_mask);
}

CImg<T> get_draw_image(const int x, const int y, const int z, const int c,
                       const CImg<T>& sprite, const float opacity) const {
  return (+*this).draw_image(x,y,z,c,sprite,opacity);
}

CImg<T> get_draw_plasma(const float alpha, const float beta, const unsigned int scale) const {
  return (+*this).draw_plasma(alpha,beta,scale);
}

CImg<T> get_draw_mandelbrot(const CImg<T>& color_palette, const float opacity,
                            const double z0r, const double z0i, const double z1r, const double z1i,
                            const unsigned int itermax, const bool normalized_iteration,
                            const bool julia_set, const double paramr, const double parami) const {
  return (+*this).draw_mandelbrot(color_palette,opacity,z0r,z0i,z1r,z1i,itermax,
                                  normalized_iteration,julia_set,paramr,parami);
}

template<typename t, typename tc>
CImg<T> get_draw_graph(const CImg<t>& data,
                       const tc *const color, const float opacity=1,
                       const unsigned int plot_type=1, const int vertex_type=1,
                       const double ymin=0, const double ymax=0,
                       const unsigned int pattern=~0U) const {
  return (+*this).draw_graph(data,color,opacity,plot_type,vertex_type,ymin,ymax,pattern);
}

template<typename tc>
CImg<T> get_draw_axes(const float x0, const float x1, const float y0, const float y1,
                      const tc *const color, const float opacity=1,
                      const int subdivisionx=-60, const int subdivisiony=-60,
                      const float precisionx=0, const float precisiony=0,
                      const unsigned int patternx=~0U, const unsigned int patterny=~0U,
                      const unsigned int font_height=13) const {
  return (+*this).draw_axes(x0,x1,y0,y1,color,opacity,subdivisionx,subdivisiony,
                            precisionx,precisiony,patternx,patterny,font_height);
}

template<typename tc>
CImg<T> get_draw_grid(const float sizex, const float sizey,
                      const float offsetx, const float offsety,
                      const bool invertx, const bool inverty,
                      const tc *const color, const float opacity=1,
                      const unsigned int patternx=~0U, const unsigned int patterny=~0U) {
  return (+*this).draw_grid(sizex,sizey,offsetx,offsety,invertx,inverty,color,opacity,
                            patternx,patterny);
}

template<typename t1, typename t2>
CImg<T> get_draw_quiver(const CImg<t1>& flow,
                        const t2 *const color, const float opacity=1,
                        const unsigned int sampling=25, const float factor=-20,
                        const bool arrows=true, const unsigned int pattern=~0U) const {
  return (+*this).draw_quiver(flow,color,opacity,sampling,factor,arrows,pattern);
}

CImg<T> get_draw_fill(const int x, const int y, const int z,
                      const T *const col, const float opacity,
                      const float tolerance, const bool is_high_connectivity) const {
  return (+*this).draw_fill(x,y,z,col,opacity,tolerance,is_high_connectivity);
}

static bool is_almost(const T x, const T c) {
  return x>=c && x<c+1;
}

template<typename tp, typename tf, typename tc, typename to>
CImg<T> get_draw_object3d(const float x0, const float y0, const float z0,
                          const CImg<tp>& vertices, const CImgList<tf>& primitives,
                          const CImgList<tc>& colors, const CImgList<to>& opacities,
                          const unsigned int render_mode, const bool double_sided,
                          const float focale,
                          const float light_x, const float light_y,const float light_z,
                          const float specular_light, const float specular_shine,
                          CImg<floatT>& zbuffer) const {
  return (+*this).draw_object3d(x0,y0,z0,vertices,primitives,colors,opacities,render_mode,
                                double_sided,focale,light_x,light_y,light_z,specular_light,
                                specular_shine,zbuffer);
}

template<typename t>
const CImg<T>& gmic_symmetric_eigen(CImg<t>& val, CImg<t>& vec) const {
  if (spectrum()!=3 && spectrum()!=6) return symmetric_eigen(val,vec);
  val.assign(width(),height(),depth(),spectrum()==3?2:3);
  vec.assign(width(),height(),depth(),spectrum()==3?2:6);
  CImg<t> _val, _vec;
  cimg_forXYZ(*this,x,y,z) {
    get_tensor_at(x,y,z).symmetric_eigen(_val,_vec);
    val.set_vector_at(_val,x,y,z);
    if (spectrum()==3) {
      vec(x,y,z,0) = _vec(0,0);
      vec(x,y,z,1) = _vec(0,1);
    } else {
      vec(x,y,z,0) = _vec(0,0);
      vec(x,y,z,1) = _vec(0,1);
      vec(x,y,z,2) = _vec(0,2);

      vec(x,y,z,3) = _vec(1,0);
      vec(x,y,z,4) = _vec(1,1);
      vec(x,y,z,5) = _vec(1,2);
    }
  }
  return *this;
}

// Append a list of 3d objects.
//-----------------------------
static CImg<T> append_CImg3d(const CImgList<T> &images) {
  if (!images) return CImg<T>();
  if (images.size()==1) return +images[0];

  unsigned int nbv = 0, nbp = 0;
  unsigned long siz = 0;
  cimglist_for(images,l) {
    const CImg<T> &img = images[l];
    if (!img.is_CImg3d(true)) return CImg<T>();
    siz+=img.size() - 8;
    nbv+=cimg::float2uint((float)img[6]);
    nbp+=cimg::float2uint((float)img[7]);
  }

  CImg<T> res(1,siz + 8);
  const T **const ptrs = new const T*[images.size()];
  T *ptrd = res._data;
  *(ptrd++) = (T)('C' + 0.5f); *(ptrd++) = (T)('I' + 0.5f); // Create object header.
  *(ptrd++) = (T)('m' + 0.5f); *(ptrd++) = (T)('g' + 0.5f);
  *(ptrd++) = (T)('3' + 0.5f); *(ptrd++) = (T)('d' + 0.5f);
  *(ptrd++) = (T)nbv;
  *(ptrd++) = (T)nbp;
  cimglist_for(images,l) { // Merge object points.
    const CImg<T>& img = images[l];
    const unsigned int nbv = cimg::float2uint((float)img[6]);
    std::memcpy(ptrd,img._data + 8,3*nbv*sizeof(T));
    ptrd+=3*nbv;
    ptrs[l] = img._data + 8 + 3*nbv;
  }
  unsigned long poff = 0;
  cimglist_for(images,l) { // Merge object primitives.
    const unsigned int
      nbv = cimg::float2uint((float)images[l][6]),
      nbp = cimg::float2uint((float)images[l][7]);
    for (unsigned int p = 0; p<nbp; ++p) {
      const unsigned int
        nbi = cimg::float2uint((float)*(ptrs[l]++)),
        _nbi = nbi<5?nbi:nbi==5?2:nbi/3;
      *(ptrd++) = (T)cimg::uint2float(nbi);
      for (unsigned int i = 0; i<_nbi; ++i) *(ptrd++) = *(ptrs[l]++) + poff;
      for (unsigned int i = nbi-_nbi; i; --i) *(ptrd++) = *(ptrs[l]++);
    }
    poff+=nbv;
  }
  unsigned long voff = 0;
  cimglist_for(images,l) { // Merge object colors.
    const unsigned int nbc = cimg::float2uint((float)images[l][7]);
    for (unsigned int c = 0; c<nbc; ++c)
      if (*(ptrs[l])==(T)-128) {
        *(ptrd++) = *(ptrs[l]++);
        const unsigned int
          w = (unsigned int)*(ptrs[l]++),
          h = (unsigned int)*(ptrs[l]++),
          s = (unsigned int)*(ptrs[l]++);
        if (!h && !s) { *(ptrd++) = (T)(w + voff); *(ptrd++) = 0; *(ptrd++) = 0; }
        else {
          *(ptrd++) = (T)w; *(ptrd++) = (T)h; *(ptrd++) = (T)s;
          const unsigned long whs = (unsigned long)w*h*s;
          std::memcpy(ptrd,ptrs[l],whs*sizeof(T));
          ptrs[l]+=whs; ptrd+=whs;
        }
      } else { *(ptrd++) = *(ptrs[l]++); *(ptrd++) = *(ptrs[l]++); *(ptrd++) = *(ptrs[l]++); }
    voff+=nbc;
  }
  voff = 0;
  cimglist_for(images,l) { // Merge object opacities.
    const unsigned int nbo = cimg::float2uint((float)images[l][7]);
    for (unsigned int o = 0; o<nbo; ++o)
      if (*(ptrs[l])==(T)-128) {
        *(ptrd++) = *(ptrs[l]++);
        const unsigned int
          w = (unsigned int)*(ptrs[l]++),
          h = (unsigned int)*(ptrs[l]++),
          s = (unsigned int)*(ptrs[l]++);
        if (!h && !s) { *(ptrd++) = (T)(w + voff); *(ptrd++) = 0; *(ptrd++) = 0; }
        else {
          *(ptrd++) = (T)w; *(ptrd++) = (T)h; *(ptrd++) = (T)s;
          const unsigned long whs = (unsigned long)w*h*s;
          std::memcpy(ptrd,ptrs[l],whs*sizeof(T));
          ptrs[l]+=whs; ptrd+=whs;
        }
      } else *(ptrd++) = *(ptrs[l]++);
    voff+=nbo;
  }
  delete[] ptrs;
  return res;
}

CImg<T>& center_CImg3d() {
  const unsigned int nbv = cimg::float2uint((float)(*this)[6]);
  const T *ptrs = data() + 8;
  float
    xm = cimg::type<float>::max(), ym = xm, zm = xm,
    xM = cimg::type<float>::min(), yM = xM, zM = xM;
  for (unsigned int i = 0; i<nbv; ++i) {
    const float x = (float)*(ptrs++), y = (float)*(ptrs++), z = (float)*(ptrs++);
    if (x<xm) xm = x; if (x>xM) xM = x;
    if (y<ym) ym = y; if (y>yM) yM = y;
    if (z<zm) zm = z; if (z>zM) zM = z;
  }
  const float xc = (xm + xM)/2, yc = (ym + yM)/2, zc = (zm + zM)/2;
  T *ptrd = data() + 8;
  for (unsigned int i = 0; i<nbv; ++i) { *(ptrd++)-=(T)xc; *(ptrd++)-=(T)yc; *(ptrd++)-=(T)zc; }
  return *this;
}

CImg<T> get_center_CImg3d() const {
  return (+*this).center_CImg3d();
}

CImg<T>& normalize_CImg3d() {
  const unsigned int nbv = cimg::float2uint((float)(*this)[6]);
  const T *ptrs = data() + 8;
  float
    xm = cimg::type<float>::max(), ym = xm, zm = xm,
    xM = cimg::type<float>::min(), yM = xM, zM = xM;
  for (unsigned int i = 0; i<nbv; ++i) {
    const float x = (float)*(ptrs++), y = (float)*(ptrs++), z = (float)*(ptrs++);
    if (x<xm) xm = x; if (x>xM) xM = x;
    if (y<ym) ym = y; if (y>yM) yM = y;
    if (z<zm) zm = z; if (z>zM) zM = z;
  }
  const float delta = cimg::max(xM-xm,yM-ym,zM-zm);
  if (delta>0) {
    T *ptrd = data() + 8;
    for (unsigned int i = 0; i<3*nbv; ++i) *(ptrd++)/=(T)delta;
  }
  return *this;
}

CImg<T> get_normalize_CImg3d() const {
  return (+*this).normalize_CImg3d();
}

template<typename t>
CImg<T>& rotate_CImg3d(const CImg<t>& rot) {
  const unsigned int nbv = cimg::float2uint((float)(*this)[6]);
  const T *ptrs = data() + 8;
  const float
    a = (float)rot(0,0), b = (float)rot(1,0), c = (float)rot(2,0),
    d = (float)rot(0,1), e = (float)rot(1,1), f = (float)rot(2,1),
    g = (float)rot(0,2), h = (float)rot(1,2), i = (float)rot(2,2);
  T *ptrd = data() + 8;
  for (unsigned int j = 0; j<nbv; ++j) {
    const float x = (float)*(ptrs++), y = (float)*(ptrs++), z = (float)*(ptrs++);
    *(ptrd++) = (T)(a*x + b*y + c*z);
    *(ptrd++) = (T)(d*x + e*y + f*z);
    *(ptrd++) = (T)(g*x + h*y + i*z);
  }
  return *this;
}

template<typename t>
CImg<T> get_rotate_CImg3d(const CImg<t>& rot) const {
  return (+*this).rotate_CImg3d(rot);
}

CImg<T>& shift_CImg3d(const float tx, const float ty, const float tz) {
  const unsigned int nbv = cimg::float2uint((float)(*this)[6]);
  T *ptrd = data() + 8;
  for (unsigned int j = 0; j<nbv; ++j) { *(ptrd++)+=(T)tx; *(ptrd++)+=(T)ty; *(ptrd++)+=(T)tz; }
  return *this;
}

CImg<T> get_shift_CImg3d(const float tx, const float ty, const float tz) const {
  return (+*this).shift_CImg3d(tx,ty,tz);
}

CImg<T>& scale_CImg3d(const float sx, const float sy, const float sz) {
  const unsigned int nbv = cimg::float2uint((float)(*this)[6]);
  T *ptrd = data() + 8;
  for (unsigned int j = 0; j<nbv; ++j) { *(ptrd++)*=(T)sx; *(ptrd++)*=(T)sy; *(ptrd++)*=(T)sz; }
  return *this;
}

CImg<T> get_scale_CImg3d(const float sx, const float sy, const float sz) const {
  return (+*this).scale_CImg3d(sx,sy,sz);
}

CImg<T>& color_CImg3d(const float R, const float G, const float B, const float opacity,
                      const bool set_RGB, const bool set_opacity) {
  T *ptrd = data() + 6;
  const unsigned int
    nbv = cimg::float2uint((float)*(ptrd++)),
    nbp = cimg::float2uint((float)*(ptrd++));
  ptrd+=3*nbv;
  for (unsigned int i = 0; i<nbp; ++i) { const unsigned int N = (unsigned int)*(ptrd++); ptrd+=N; }
  for (unsigned int c = 0; c<nbp; ++c)
    if (*ptrd==(T)-128) {
      ++ptrd;
      const unsigned int
        w = (unsigned int)*(ptrd++),
        h = (unsigned int)*(ptrd++),
        s = (unsigned int)*(ptrd++);
      ptrd+=w*h*s;
    } else if (set_RGB) { *(ptrd++) = (T)R; *(ptrd++) = (T)G; *(ptrd++) = (T)B; } else ptrd+=3;
  if (set_opacity)
    for (unsigned int o = 0; o<nbp; ++o)
      if (*ptrd==(T)-128) {
        ++ptrd;
        const unsigned int
          w = (unsigned int)*(ptrd++),
          h = (unsigned int)*(ptrd++),
          s = (unsigned int)*(ptrd++);
        ptrd+=w*h*s;
      } else *(ptrd++) = (T)opacity;
  return *this;
}

CImg<T> get_color_CImg3d(const float R, const float G, const float B,
                         const float opacity, const bool set_RGB, const bool set_opacity) const {
  return (+*this).color_CImg3d(R,G,B,opacity,set_RGB,set_opacity);
}

CImg<T>& texturize_CImg3d(const CImg<T>& texture, const CImg<T>& coords) {
  return get_texturize_CImg3d(texture,coords).move_to(*this);
}

CImg<T> get_texturize_CImg3d(const CImg<T>& texture, const CImg<T>& coords) const {
  CImgList<uintT> primitives;
  CImgList<T> colors;
  CImgList<floatT> opacities;
  const CImg<floatT> points = get_CImg3dtoobject3d(primitives,colors,opacities);
  points.texturize_object3d(primitives,colors,texture,coords);
  return points.get_object3dtoCImg3d(primitives,colors,opacities);
}

template<typename t>
CImg<T>& inpaint(const CImg<t>& mask) {
  if (!is_sameXYZ(mask))
    throw CImgArgumentException("CImg<%s>::inpaint(): Invalid mask (%u,%u,%u,%u,%p) for "
                                "instance image (%u,%u,%u,%u,%p).",
                                pixel_type(),mask._width,mask._height,mask._depth,
                                mask._spectrum,mask._data,
                                _width,_height,_depth,_spectrum,_data);
  CImg<t> _mask(mask,false), _nmask(mask,false);
  CImg_3x3(M,t); Mpp = Mnp = Mpn = Mnn = 0;
  CImg_3x3(I,T); Ipp = Inp = Icc = Ipn = Inn = 0;
  bool is_pixel = false;
  do {
    is_pixel = false;
    cimg_forZ(_mask,z) cimg_for3x3(_mask,x,y,z,0,M,t) if (Mcc && (!Mpc || !Mnc || !Mcp || !Mcn)) {
      is_pixel = true;
      const float
        wcp = Mcp?0.0f:1.0f,
        wpc = Mpc?0.0f:1.0f,
        wnc = Mnc?0.0f:1.0f,
        wcn = Mcn?0.0f:1.0f,
        sumw = wcp + wpc + wnc + wcn;
      cimg_forC(*this,k) {
        cimg_get3x3(*this,x,y,z,k,I,T);
        (*this)(x,y,z,k) = (T)((wcp*Icp + wpc*Ipc + wnc*Inc + wcn*Icn)/sumw);
      }
      _nmask(x,y,z) = 0;
    }
    _mask = _nmask;
  } while (is_pixel);
  return *this;
}

template<typename t>
CImg<T> get_inpaint(const CImg<t>& mask) const {
  return (+*this).inpaint(mask);
}

CImg<T>& mark() {
  unsigned int siz = _width;
  if (siz<2) assign(siz=2,1,1,1,0); else if (_data[siz-2]) resize(++siz,1,1,1,0);
  T &last = _data[siz-1];
  if (last<cimg::type<T>::max()) ++last;
  return *this;
}

CImg<T> get_mark() const {
  return (+*this).mark();
}

CImg<T>& copymark() {
  return get_copymark().move_to(*this);
}

CImg<T> get_copymark() const {
  if (is_empty()) return CImg<T>::string("~");
  CImg<T> res = get_resize(_width+1,1,1,1,0);
  const char *const ext = cimg::split_filename(_data);
  if (*ext) {
    const int l = (int)(ext - _data - 1);
    if (l>0) {
      if (_data[l-1]=='~') return +*this;
      std::memcpy(res._data,_data,l);
    }
    res[l] = '~'; res[l+1] = '.';
    std::memcpy(res._data+l+2,ext,_data+_width-ext);
  } else {
    const unsigned int l = (int)(ext - _data);
    if (_data[l-1]=='~' || (l>1 && _data[l-1]==']' && _data[l-2]=='~')) return +*this;
    std::memcpy(res._data,_data,l);
    res[l] = '~';
    if (ext>_data && *(ext-1)==']') cimg::swap(res[l],res[l-1]);
    std::memcpy(res._data+l+1,ext,_data+_width-ext);
  }
  return res;
}

//! Display informations about an image data (special formatting for G'MIC).
const CImg<T>& gmic_print(const char *const title=0, const bool is_debug=false) const {
  int xm = 0, ym = 0, zm = 0, vm = 0, xM = 0, yM = 0, zM = 0, vM = 0;
  static CImg<doubleT> st;
  if (!is_empty()) {
    st = get_stats();
    xm = (int)st[4]; ym = (int)st[5], zm = (int)st[6], vm = (int)st[7];
    xM = (int)st[8]; yM = (int)st[9], zM = (int)st[10], vM = (int)st[11];
  }
  const unsigned long siz = size(), msiz = siz*sizeof(T), siz1 = siz-1,
    mdisp = msiz<8*1024?0:(msiz<8*1024*1024?1:2),
    wh = _width*_height, whd = _width*_height*_depth,
    w1 = _width-1, wh1 = _width*_height-1, whd1 = _width*_height*_depth-1;

  char _title[64] = { 0 };
  if (!title) cimg_snprintf(_title,sizeof(_title),"CImg<%s>",pixel_type());

  std::fprintf(cimg::output(),"%s%s%s%s:\n  %ssize%s = (%u,%u,%u,%u) [%lu %s].\n  %sdata%s = %s",
               cimg::t_magenta,cimg::t_bold,title?title:_title,cimg::t_normal,
               cimg::t_bold,cimg::t_normal,_width,_height,_depth,_spectrum,
               mdisp==0?msiz:(mdisp==1?(msiz>>10):(msiz>>20)),
               mdisp==0?"b":(mdisp==1?"Kio":"Mio"),
               cimg::t_bold,cimg::t_normal,
               is_debug?"":"(");
  if (is_debug) std::fprintf(cimg::output(),"%p = (",_data);
  if (!is_empty()) cimg_foroff(*this,off) {
      std::fprintf(cimg::output(),cimg::type<T>::format(),cimg::type<T>::format(_data[off]));
      if (off!=siz1) std::fprintf(cimg::output(),"%s",
                                  off%whd==whd1?"^":
                                  off%wh==wh1?"\\":
                                  off%_width==w1?";":",");
      if (off==11 && siz>24) { off = siz1-12; std::fprintf(cimg::output(),"... "); }
    }
  if (is_empty()) std::fprintf(cimg::output(),") [%s].\n",
                               pixel_type());
  else std::fprintf(cimg::output(),") [%s%s].\n  %smin%s = %g, %smax%s = %g, %smean%s = %g, "
                    "%sstd%s = %g, %scoords_min%s = (%u,%u,%u,%u), "
                    "%scoords_max%s = (%u,%u,%u,%u).\n",
                    _is_shared?"shared ":"",pixel_type(),
                    cimg::t_bold,cimg::t_normal,st[0],
                    cimg::t_bold,cimg::t_normal,st[1],
                    cimg::t_bold,cimg::t_normal,st[2],
                    cimg::t_bold,cimg::t_normal,std::sqrt(st[3]),
                    cimg::t_bold,cimg::t_normal,xm,ym,zm,vm,
                    cimg::t_bold,cimg::t_normal,xM,yM,zM,vM);
  std::fflush(cimg::output());
  return *this;
}

//--------------- End of CImg plug-in ----------------------------

#else // #ifdef cimg_plugin

#include "gmic.h"
#if defined(gmic_float)
#include "gmic_def.h"
#else // #ifdef gmic_float
extern char data_gmic_def[];
extern unsigned int size_data_gmic_def;
#endif // #ifdef gmic_float

using namespace cimg_library;
#undef min
#undef max

// Define some useful variables and macros.
//------------------------------------------

// End character.
static char end = 0;

// Ellipsize a string.
#define gmic_ellipsize(s,l) { if (l>=5 && s[l-2]) s[l-4] = s[l-3] = s[l-2] = '.'; }

// Return current selection as a selection string.
#define gmic_selection selection2string(selection,images_names,true)

// Return image argument as a shared or non-shared copy of one existing image.
inline bool _gmic_image_arg(const unsigned int ind, const CImg<unsigned int>& selection) {
  cimg_forY(selection,l) if (selection[l]==ind) return true;
  return false;
}
#define gmic_image_arg(ind) (_gmic_image_arg(ind,selection)?images[ind]:images[ind].get_shared())

// Code for managing argument substitutions from a command.
inline const char *gmic_ellipsize_arg(const char *const argument, CImg<char>& argument_text) {
  if (argument_text) return argument_text;
  const unsigned int l = std::strlen(argument);
  if (l>=72) {
    argument_text.assign(72);
    std::memcpy(argument_text.data(),argument,32);
    std::memcpy(argument_text.data()+32," ... ",5);
    std::memcpy(argument_text.data()+37,argument+l-34,35); // Last '\0' is included.
  }
  return argument_text?argument_text:argument;
}

#define gmic_substitute_args() { \
  const char *const argument0 = argument; \
  substitute_item(argument,images,images_names,variables_sizes).move_to(_argument); \
  argument_text = gmic_ellipsize_arg(argument=argument_text=_argument,_argument_text); \
  if (is_debug) { \
    if (std::strcmp(argument,argument0)) debug(images,"Command '%s' : arguments = '%s' -> '%s'.", \
                                               command,argument0,argument); \
    else debug(images,"Command '%s' : arguments = '%s'.", \
               command,argument0); \
  }}

// Code for having 'get' or 'non-get' versions of G'MIC commands.
#define gmic_apply(instance,function) { \
  unsigned int posi = 0; \
  const bool is_inlist = images.contains(instance,posi); \
  if (is_get_version) { \
    instance.get_##function.move_to(images); \
    if (is_inlist) images_names[posi].get_copymark().mark().move_to(images_names); \
    else CImg<char>::string("[unnamed]").move_to(images_names); \
  } else { instance.function; images_names[posi].mark(); } \
}

// Code for simple commands that has no arguments and act on images.
#define gmic_simple_item(option,function,description) \
  if (!std::strcmp(option,command)) { \
    print(images,description,gmic_selection); \
    cimg_forY(selection,l) gmic_apply(images[selection[l]],function()); \
    is_released = false; continue; \
}

// Code for the type cast command.
#define gmic_cast(pixel_type,st_type) \
  if (!std::strcmp(argument,#pixel_type)) { \
    if (std::strcmp(st_type,cimg::type<T>::string())) { \
      if (!is_default_type) { --position; break; } \
      else { \
        print(images,"Set pixel data type to '%s'.",st_type); \
        CImgList<pixel_type> cast_images; \
        images.move_to(cast_images); \
        is_default_type = false; \
        is_released = false; \
        parse_##pixel_type(commands_line,++position,cast_images,images_names,variables_sizes); \
        is_default_type = true; \
        cast_images.move_to(images); \
      } \
    } else { print(images,"Set pixel data type to '%s'.",st_type); ++position; } \
    continue; \
  }

// Code for G'MIC arithmetic commands.
#define gmic_arithmetic_item(command_name,\
                             function1,description1,arg1_1,arg1_2,arg1_3,value_type1, \
                             function2,description2,arg2_1,arg2_2, \
                             description3,arg3_1,arg3_2, \
                             description4) \
 if (!std::strcmp(command_name,command)) { \
   gmic_substitute_args(); \
   CImg<unsigned int> ind; \
   double value = 0; \
   char sep = 0; \
   *indices = *formula = 0; \
   if (std::sscanf(argument,"%lf%c",&value,&end)==1 || \
       (std::sscanf(argument,"%lf%c%c",&value,&sep,&end)==2 && sep=='%')) { \
      const char *const ssep = sep=='%'?"%":""; \
      print(images,description1 ".",arg1_1,arg1_2,arg1_3); \
      cimg_forY(selection,l) { \
       CImg<T> &img = images[selection[l]]; \
       double nvalue = value; \
       if (sep=='%' && img) { \
         double vmin = 0, vmax = (double)img.max_min(vmin); \
         nvalue = vmin + (vmax-vmin)*value/100; \
       } \
       if (is_get_version) { \
         images_names.insert(images_names[selection[l]].get_copymark().mark()); \
         images.insert(img); images.back().function1((value_type1)nvalue); \
       } else { \
         images_names[selection[l]].mark(); \
         img.function1((value_type1)nvalue); \
       } \
      } \
      ++position; \
   } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 && \
              sep==']' \
              && (ind=selection2cimg(indices,images.size(),images_names,command_name,\
                                     true,false,CImg<char>::empty())).  \
              height()==1) { \
     print(images,description2 ".",arg2_1,arg2_2); \
     const CImg<T> img0 = gmic_image_arg(*ind); \
     cimg_forY(selection,l) \
       if (is_get_version) { \
         images_names.insert(images_names[selection[l]].get_copymark().mark()); \
         images.insert(images[selection[l]]); images.back().function2(img0); \
       } else { \
         images_names[selection[l]].mark(); \
         images[selection[l]].function2(img0); \
       } \
     ++position; \
   } else if (std::sscanf(argument,"'%4095[^']%c%c",formula,&sep,&end)==2 && sep=='\'') { \
     gmic_strreplace(formula); print(images,description3 ".",arg3_1,arg3_2); \
     cimg_forY(selection,l) \
       if (is_get_version) { \
         images_names.insert(images_names[selection[l]].get_copymark().mark()); \
         images.insert(images[selection[l]]); images.back().function2((const char*)formula); \
       } else { \
         images_names[selection[l]].mark(); \
         images[selection[l]].function2((const char*)formula); \
       } \
     ++position; \
   } else { \
     print(images,description4 ".",gmic_selection); \
     if (images && selection) { \
       if (is_get_version) { \
         CImg<T> img0 = images[selection[0]]; \
         for (unsigned int l = 1; l<(unsigned int)selection.height(); ++l) \
           img0.function2(images[selection[l]]); \
         images_names.insert(images_names[selection[0]].get_copymark().mark()); \
         img0.move_to(images); \
       } else if (selection.height()>=2) { \
       const unsigned int ind0 = selection[0]; \
       for (unsigned int l = 1; l<(unsigned int)selection.height(); ++l) \
         images[ind0].function2(images[selection[l]]); \
       images_names[ind0].mark(); \
       remove_images(images,images_names,selection,1,selection.height()-1); \
       }}} is_released = false; continue; \
   }

// Return a 8-bits hashcode from a string.
//----------------------------------------
inline unsigned int gmic_hashcode(const char *const str, const bool is_variable) {
  if (!str) return 0;
  unsigned int hash = 0;
  if (is_variable) {
    if (*str=='_') return 255;
    for (const char *s = str; *s; ++s) hash+=*s;
    return hash%255;
  }
  for (const char *s = str; *s; ++s) hash+=*s;
  return hash&255;
}

// Tells if the the implementation of a G'MIC command contains arguments.
//------------------------------------------------------------------------
inline bool gmic_command_has_arguments(const char *const command) {
  if (!command || !*command) return false;
  for (const char *s = std::strchr(command,'$'); s; s = std::strchr(s,'$')) {
    const char c = *(++s);
    if (c=='#' ||
        c=='*' ||
        c=='=' ||
        (c>'0' && c<='9') ||
        (c=='-' && *(s+1)>'0' && *(s+1)<='9') ||
        (c=='{' && (*(s+1)=='^' ||
                    (*(s+1)>'0' && *(s+1)<='9') ||
                    (*(s+1)=='-' && *(s+2)>'0' && *(s+2)<='9')))) return true;
  }
  return false;
}

// Compute the basename of an image name.
//---------------------------------------
inline const char* gmic_basename(const char *const s)  {
  if (!s) return s;
  const unsigned int l = (unsigned int)std::strlen(s);
  if (*s=='[' && (s[l-1]==']' || s[l-1]=='.')) return s;
  const char *p = 0;
  for (const char *np = s; np>=s && (p=np); np = std::strchr(np,cimg_file_separator)+1) {}
  return p;
}

// Return Levenshtein distance between two strings.
// (adapted from http://rosettacode.org/wiki/Levenshtein_distance#C)
//------------------------------------------------------------------
static int _gmic_levenshtein(const char *const s, const char *const t,
                             CImg<int>& d, const int i, const int j) {
  const int ls = d.width()-1, lt = d.height()-1;
  if (d(i,j)>=0) return d(i,j);
  int x;
  if (i==ls) x = lt - j;
  else if (j==lt) x = ls - i;
  else if (s[i]==t[j]) x = _gmic_levenshtein(s,t,d,i+1,j+1);
  else {
    x = _gmic_levenshtein(s,t,d,i+1,j+1);
    int y;
    if ((y=_gmic_levenshtein(s,t,d,i,j+1))<x) x = y;
    if ((y=_gmic_levenshtein(s,t,d,i+1,j))<x) x = y;
    ++x;
  }
  return d(i,j) = x;
}

inline int gmic_levenshtein(const char *const s, const char *const t) {
  const char *const ns = s?s:"", *const nt = t?t:"";
  const int ls = std::strlen(ns), lt = std::strlen(nt);
  if (!ls) return lt; else if (!lt) return ls;
  CImg<int> d(1+ls,1+lt,1,1,-1);
  return _gmic_levenshtein(ns,nt,d,0,0);
}

// Constructors / destructors.
//----------------------------
#if defined(gmic_float) || !defined(gmic_split_compilation)

CImgList<char> gmic::default_commands_names[256] = {};
CImgList<char> gmic::default_commands[256] = {};
CImgList<char> gmic::default_commands_has_arguments[256] = {};
bool gmic::is_default_commands = false;

gmic::~gmic() {
  debug("%sEnd G'MIC instance.%s\n",cimg::t_bold,cimg::t_normal);
}

gmic::gmic(const char *const commands_line, const char *const custom_commands,
           const bool include_default_commands, float *const p_progress, int *const p_cancel) {
  CImgList<float> images;
  CImgList<char> images_names;
  _gmic(commands_line,images,images_names,custom_commands,include_default_commands,
        p_progress,p_cancel);
}

// Get current scope as a string.
//-------------------------------
CImg<char> gmic::scope2string(const bool is_last_slash) const {
  CImgList<char> res;
  const unsigned int siz = (unsigned int)scope.size();
  if (siz<=8) res.assign(scope);
  else {
    res.assign(8);
    res[0].assign(scope[0]);
    res[1].assign(scope[1]);
    res[2].assign(scope[2]);
    res[3].assign("..",3);
    res[4].assign(scope[siz-4]);
    res[5].assign(scope[siz-3]);
    res[6].assign(scope[siz-2]);
    res[7].assign(scope[siz-1]);
  }
  cimglist_for(res,l) res[l].back() = '/';
  if (!is_last_slash) --(res.back()._width);
  CImg<char>::vector(0).move_to(res);
  return res>'x';
}

CImg<char> gmic::scope2string(const CImg<unsigned int>& scope_selection,
                              const bool is_last_slash) const {
  const CImg<char> def_scope("./",3);
  if (!scope_selection) return def_scope;
  CImgList<char> res(scope_selection.height());
  cimglist_for(res,l) res[l].assign(scope[scope_selection(l)]).back() = '/';
  if (!is_last_slash) --(res.back()._width);
  CImg<char>::vector(0).move_to(res);
  return res>'x';
}

// Parse items from a G'MIC command line.
//---------------------------------------
CImgList<char> gmic::commands_line_to_CImgList(const char *const commands_line) {
  if (!commands_line || !*commands_line) return CImgList<char>();
  bool is_dquoted = false;
  const char *ptrs0 = commands_line;
  while (*ptrs0==' ') ++ptrs0;  // Remove leading spaces to first item.
  CImg<char> item(std::strlen(ptrs0)+1);
  CImgList<char> items;
  char *ptrd = item.data(), c = 0;
  for (const char *ptrs = ptrs0; *ptrs; ++ptrs) {
    c = *ptrs;
    if (c=='\\') {  // If escaped character.
      c = *(++ptrs);
      if (!c) { c = '\\'; --ptrs; }
      else if (c=='$') c = _dollar;
      else if (c=='{') c = _lbrace;
      else if (c=='}') c = _rbrace;
      else if (c==',') c = _comma;
      else if (c=='\"') c = _dquote;
      else if (c=='@') c = _arobace;
      else if (c==' ') c = ' ';
      else *(ptrd++) = '\\';
      *(ptrd++) = c;
    } else if (is_dquoted) { // If non-escaped character inside string.
      if (c=='\"') is_dquoted = false;
      else *(ptrd++) = c=='$'?_dollar:c=='{'?_lbrace:c=='}'?_rbrace:
             c==','?_comma:c=='@'?_arobace:c;
    } else { // Non-escaped character outside string.
      if (c=='\"') is_dquoted = true;
      else if (c==' ') {
        *ptrd = 0; CImg<char>(item.data(),ptrd - item.data() + 1).move_to(items);
        ptrd = item.data();
        ++ptrs; while (*ptrs==' ') ++ptrs; ptrs0 = ptrs--;  // Remove trailing spaces to next item.
      } else *(ptrd++) = c;
    }
  }
  if (is_dquoted) error("Invalid command line: Double quotes are not closed, in expression '%s'.",
                        commands_line);
  if (ptrd!=item.data() && c!=' ') {
    *ptrd = 0; CImg<char>(item.data(),ptrd - item.data() + 1).move_to(items);
  }
  if (is_debug) {
    debug("Decompose command line into %u items: ",items.size());
    cimglist_for(items,l) debug("  item[%u] = '%s'",l,items[l].data());
  }
  return items;
}

// Set default G'MIC environment.
//-------------------------------
gmic& gmic::assign(const char *const custom_commands, const bool include_default_commands,
                   float *const p_progress, int *const p_cancel) {
  std::setlocale(LC_NUMERIC,"C");
  verbosity = 0;
  nb_carriages = 0;
  is_released = true;
  is_debug = false;
  is_start = true;
  is_quit = false;
  is_return = false;
  is_double3d = true;
  is_default_type = true;
  check_elif = false;
  background3d.assign(1,2,1,3).fill(32,64,32,116,64,96).resize(1,256,1,3,3);
  render3d = 4;
  renderd3d = -1;
  focale3d = 800;
  light3d.assign();
  light3d_x = light3d_y = 0;
  light3d_z = -5e8;
  specular_lightness3d = 0.15f;
  specular_shininess3d = 0.8f;
  if (p_progress) progress = p_progress; else { _progress = -1; progress = &_progress; }
  if (p_cancel) cancel = p_cancel; else { _cancel = 0; cancel = &_cancel; }
  for (unsigned int l = 0; l<256; ++l) {
    commands_names[l].assign();
    commands[l].assign();
    commands_has_arguments[l].assign(); }
  if (include_default_commands) {
    if (!is_default_commands) {
      add_commands(data_gmic_def,default_commands_names,default_commands,
                   default_commands_has_arguments);
      is_default_commands = true;
    }
    for (unsigned int l = 0; l<256; ++l) {
      commands_names[l].assign(default_commands_names[l]);
      commands[l].assign(default_commands[l]);
      commands_has_arguments[l].assign(default_commands_has_arguments[l]);
    }
  }
  add_commands(custom_commands,commands_names,commands,commands_has_arguments);
  for (unsigned int l = 0; l<256; ++l) { variables[l].assign(); variables_names[l].assign(); }
#if gmic_is_beta==1
  const char *const st_gmic_is_beta = "_gmic_is_beta";
  const unsigned int hashcode = gmic_hashcode(st_gmic_is_beta,true);
  CImg<char>::string(st_gmic_is_beta).move_to(variables_names[hashcode]);
  CImg<char>::string("1").move_to(variables[hashcode]);
#endif // #if gmic_is_beta==1
  return *this;
}

// Print log message.
//-------------------
gmic& gmic::print(const char *format, ...) {
  if (verbosity<0 && !is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  CImg<char> message(16384);
  cimg_vsnprintf(message,message.width(),format,ap);
  gmic_ellipsize(message,message.width());
  va_end(ap);
  gmic_strreplace(message);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  std::fprintf(cimg::output(),
               "[gmic]%s %s",
               scope2string().data(),message.data());
  std::fflush(cimg::output());
  return *this;
}

// Print warning message.
//-----------------------
gmic& gmic::warn(const char *format, ...) {
  if (verbosity<0 && !is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  static char message[1024+128];
  cimg_snprintf(message,128,"*** Warning in %s *** ",scope2string().data());
  cimg_vsnprintf(message + std::strlen(message),1024,format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  gmic_strreplace(message);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  std::fprintf(cimg::output(),
               "%s[gmic]%s %s%s%s",
               cimg::t_red,scope2string().data(),cimg::t_bold,message,cimg::t_normal);
  std::fflush(cimg::output());
  return *this;
}

// Print error message, and quit interpreter.
//-------------------------------------------
gmic& gmic::error(const char *const format, ...) {
  va_list ap;
  va_start(ap,format);
  static char message[1024+128];
  cimg_snprintf(message,128,"*** Error in %s *** ",scope2string().data());
  cimg_vsnprintf(message + std::strlen(message),1024,format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  gmic_strreplace(message);
  CImg<char>::string(message).move_to(status);
  if (verbosity>=0 || is_debug) {
    if (*message!='\r')
      for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
    nb_carriages = 1;
    std::fprintf(cimg::output(),"[gmic]%s %s%s%s%s",
                 scope2string().data(),cimg::t_bold,cimg::t_red,message,cimg::t_normal);
    std::fflush(cimg::output());
  }
  throw gmic_exception(0,message);
  return *this;
}

// Print debug message.
//---------------------
gmic& gmic::debug(const char *format, ...) {
  if (!is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  static char message[1024];
  cimg_vsnprintf(message,sizeof(message),format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  std::fprintf(cimg::output(),
               "%s<gmic>%s ",
               cimg::t_green,scope2string().data());
  for (char *s = message; *s; ++s) {
    char c = *s;
    if (c<' ') switch (c) {
      case _dollar : std::fprintf(cimg::output(),"\\$"); break;
      case _lbrace : std::fprintf(cimg::output(),"\\{"); break;
      case _rbrace : std::fprintf(cimg::output(),"\\}"); break;
      case _comma : std::fprintf(cimg::output(),"\\,"); break;
      case _dquote : std::fprintf(cimg::output(),"\\\""); break;
      case _arobace : std::fprintf(cimg::output(),"\\@"); break;
      default : std::fputc(c,cimg::output());
      }
    else std::fputc(c,cimg::output());
  }
  std::fprintf(cimg::output(),
               "%s",
               cimg::t_normal);
  std::fflush(cimg::output());
  return *this;
}

// Add custom commands from a char* buffer.
//------------------------------------------
gmic& gmic::add_commands(const char *const data_commands,
                         CImgList<char> (&commands_names)[256],
                         CImgList<char> (&commands)[256],
                         CImgList<char> (&commands_has_arguments)[256]) {
  if (!data_commands || !*data_commands) return *this;
  static char mac[256], com[256*1024], line[256*1024];
  unsigned int pos[256] = { 0 };
  *mac = *com = *line = 0;
  bool is_last_slash = false, _is_last_slash = false;
  int ind = -1;
  char sep = 0;
  for (const char *data = data_commands; *data; is_last_slash = _is_last_slash) {
    // Read new line.
    char *_line = line;
    while (*data!='\n' && *data && _line<line+sizeof(line)) *(_line++) = *(data++); *_line = 0;
    if (*data=='\n') ++data; // Skip next '\n'.
    // Replace non-usual characters by spaces.
    for (_line = line; *_line; ++_line) if ((unsigned char)*_line<' ') *_line = ' ';
    _line = line; if (*_line=='#') *_line = 0; else do { // Remove comments.
        if ((_line=std::strchr(_line,'#')) && *(_line-1)==' ') { *--_line = 0; break; }
      } while (_line++);
    // Remove useless trailing spaces.
    char *linee = line + std::strlen(line) - 1;
    while (*linee==' ' && linee>=line) --linee; *(linee+1) = 0;
    char *lines = line; while (*lines==' ') ++lines; // Remove useless leading spaces.
    // Check if last character is a '\'...
    _is_last_slash = false;
    for (_line = linee; *_line=='\\' && _line>=lines; --_line) _is_last_slash = !_is_last_slash;
    if (_is_last_slash) *(linee--) = 0; // .. and remove it if necessary.
    if (!*lines) continue; // Empty line found.
    *mac = *com = 0;
    if (!is_last_slash && std::strchr(lines,':') && // Check for a command definition.
        std::sscanf(lines,"%255[a-zA-Z0-9_] %c %262143[^\n]",mac,&sep,com)>=2 &&
        (*lines<'0' || *lines>'9') && sep==':') {
      ind = gmic_hashcode(mac,false);
      CImg<char>::string(mac).move_to(commands_names[ind],pos[ind]);
      CImg<char> body = CImg<char>::string(com);
      CImg<char>::vector((char)gmic_command_has_arguments(body)).
        move_to(commands_has_arguments[ind],pos[ind]);
      body.move_to(commands[ind],pos[ind]++);

    } else { // Continuation of a previous line.
      if (ind<0) error("Command 'command': Syntax error in expression '%s'.",lines);
      const unsigned int p = pos[ind] - 1;
      if (!is_last_slash) commands[ind][p].back() = ' ';
      else --(commands[ind][p]._width);
      const CImg<char> body = CImg<char>(lines,linee - lines + 2);
      commands_has_arguments[ind](p,0) |= (char)gmic_command_has_arguments(body);
      commands[ind][p].append(body,'x');
    }
  }
  return *this;
}

// Add commands from a file.
//---------------------------
gmic& gmic::add_commands(std::FILE *const file,
                         CImgList<char> (&commands_names)[256],
                         CImgList<char> (&commands)[256],
                         CImgList<char> (&commands_has_arguments)[256]) {
  if (!file) return *this;
  long siz = 0;
  std::fseek(file,0,SEEK_END);
  siz = std::ftell(file);
  std::rewind(file);
  if (siz>0) {
    CImg<char> buffer(siz+1);
    if (std::fread(buffer.data(),sizeof(char),siz,file)) {
      buffer[siz] = 0;
      try { add_commands(buffer.data(),commands_names,commands,commands_has_arguments); }
      catch (...) { std::fclose(file); throw; }
    }
  }
  return *this;
}

// Return subset indices from a selection string.
//-----------------------------------------------
CImg<unsigned int> gmic::selection2cimg(const char *const string, const unsigned int indice_max,
                                        const CImgList<char>& names,
                                        const char *const command, const bool is_selection,
                                        const bool allow_new_name, CImg<char> &new_name) {
  if (string && !*string) return CImg<unsigned int>(); // Empty selection.
  if (!string || (*string=='^' && !string[1])) { // Whole selection.
    if (indice_max) return CImg<unsigned int>::sequence(indice_max,0,indice_max-1);
    else return CImg<unsigned int>();
  }
  const char *const stype = is_selection?"selection":"subset";
  const int
    ctypel = is_selection?'[':'{',
    ctyper = is_selection?']':'}';
  CImg<bool> is_selected(1,indice_max,1,1,false);
  const bool is_inverse = *string=='^';
  const char *it = string + (is_inverse?1:0);
  for (bool stopflag = false; !stopflag; ) {
    static char name[256];
    CImg<char> item;
    float ind0 = 0, ind1 = 0, step = 1;
    int iind0 = 0, iind1 = 0;
    bool is_label = false;
    char sep = 0;

    const char *const it_comma = std::strchr(it,',');
    if (it_comma) { item.assign(it,it_comma-it+1); item.back() = 0; it = it_comma + 1; }
    else { CImg<char>::string(it).move_to(item); stopflag = true; }

    char *const it_colon = std::strchr(item,':');
    if (it_colon) {
      *it_colon = 0;
      if (std::sscanf(it_colon+1,"%f%c",&step,&end)!=1 || step<=0)
        error("Command '%s': Invalid %s %c%s%c (syntax error after colon ':').",
              command,stype,ctypel,string,ctyper);
    }
    if (std::sscanf(item,"%f%c",&ind0,&end)==1) { // Single indice.
      iind1 = iind0 = (int)cimg::round(ind0);
    } else if (std::sscanf(item,"%f-%f%c",&ind0,&ind1,&end)==2) { // Sequence between 2 indices.
      iind0 = (int)cimg::round(ind0);
      iind1 = (int)cimg::round(ind1);
    } else if (std::sscanf(item,"%255[a-zA-Z0-9_]%c",name,&end)==1 && // Label.
               (*name<'0' || *name>'9')) {
      cimglist_for(names,l) if (names[l] && !std::strcmp(names[l],name)) {
        is_selected(l) = true; is_label = true;
      }
      if (!is_label) {
        if (allow_new_name && !new_name) {
          iind0 = iind1 = -1;
          CImg<char>::string(name).move_to(new_name);
        } else error("Command '%s': Invalid %s %c%s%c (undefined label '%s').",
                     command,stype,ctypel,string,ctyper,name);
      }
    } else if (std::sscanf(item,"%f%c%c",&ind0,&sep,&end)==2 && sep=='%') { // Single percent.
      iind1 = iind0 = (int)cimg::round(ind0*(indice_max-1)/100);
    } else if (std::sscanf(item,"%f%%-%f%c%c",&ind0,&ind1,&sep,&end)==3 && sep=='%') {
      // Sequence between 2 percents.
      iind0 = (int)cimg::round(ind0*(indice_max-1)/100);
      iind1 = (int)cimg::round(ind1*(indice_max-1)/100);
    } else if (std::sscanf(item,"%f%%-%f%c",&ind0,&ind1,&end)==2) {
      // Sequence between a percent and an indice.
      iind0 = (int)cimg::round(ind0*(indice_max-1)/100);
      iind1 = (int)cimg::round(ind1);
    } else if (std::sscanf(item,"%f-%f%c%c",&ind0,&ind1,&sep,&end)==3 && sep=='%') {
      // Sequence between an indice and a percent.
      iind0 = (int)cimg::round(ind0);
      iind1 = (int)cimg::round(ind1*(indice_max-1)/100);
    } else error("Command '%s': Invalid %s %c%s%c.",
                 command,stype,ctypel,string,ctyper);

    if (!indice_max) error("Command '%s': Invalid %s %c%s%c (no data available).",
                           command,stype,ctypel,string,ctyper);
    if (!is_label) {
      int
        uind0 = iind0<0?iind0+indice_max:iind0,
        uind1 = iind1<0?iind1+indice_max:iind1;
      if (uind0>uind1) { cimg::swap(uind0,uind1); cimg::swap(iind0,iind1); }
      if (uind0<0 || uind0>=(int)indice_max)
        error("Command '%s': Invalid %s %c%s%c (contains starting indice '%d', "
              "not in range -%u..%u).",
              command,stype,ctypel,string,ctyper,iind0,indice_max,indice_max-1);
      if (uind1<0 || uind1>=(int)indice_max)
        error("Command '%s': Invalid %s %c%s%c (contains ending indice '%d', "
              "not in range -%u..%u).",
              command,stype,ctypel,string,ctyper,iind1,indice_max,indice_max-1);
      for (int l = uind0; l<=uind1; l+=step) is_selected[l] = true;
    }
  }
  unsigned int indice = 0;
  cimg_for(is_selected,p,bool) if (*p) ++indice;
  CImg<unsigned int> selection(1,is_inverse?indice_max-indice:indice);
  indice = 0;
  if (is_inverse) { cimg_forY(is_selected,l) if (!is_selected[l]) selection[indice++] = l; }
  else cimg_forY(is_selected,l) if (is_selected[l]) selection[indice++] = l;
  return selection;
}

// Return selection or filename strings from a set of indices.
//------------------------------------------------------------
char *gmic::selection2string(const CImg<unsigned int>& selection,
                             const CImgList<char>& images_names,
                             const bool display_indices) const {
  static char res0[1024], res1[1024];
  if (display_indices) {
    switch (selection.height()) {
    case 0: cimg_snprintf(res0,sizeof(res0)," []"); break;
    case 1: cimg_snprintf(res0,sizeof(res0)," [%u]",
                          selection[0]); break;
    case 2: cimg_snprintf(res0,sizeof(res0),"s [%u,%u]",
                          selection[0],selection[1]); break;
    case 3: cimg_snprintf(res0,sizeof(res0),"s [%u,%u,%u]",
                          selection[0],selection[1],selection[2]); break;
    case 4: cimg_snprintf(res0,sizeof(res0),"s [%u,%u,%u,%u]",
                          selection[0],selection[1],selection[2],selection[3]); break;
    default: cimg_snprintf(res0,sizeof(res0),"s [%u,..,%u]",
                           selection[0],selection.back());
    }
    return res0;
  }
  switch (selection.height()) {
  case 0:
    *res1 = 0;
    break;
  case 1:
    cimg_snprintf(res1,sizeof(res1),"%s%s",
                  gmic_basename(images_names[selection[0]].data()),
                  images_names[selection[0]].back()?"*":"");
    break;
  case 2:
    cimg_snprintf(res1,sizeof(res1),"%s%s, %s%s",
                  gmic_basename(images_names[selection[0]].data()),
                  images_names[selection[0]].back()?"*":"",
                  gmic_basename(images_names[selection[1]].data()),
                  images_names[selection[1]].back()?"*":"");
    break;
  case 3:
    cimg_snprintf(res1,sizeof(res1),"%s%s, %s%s, %s%s",
                  gmic_basename(images_names[selection[0]].data()),
                  images_names[selection[0]].back()?"*":"",
                  gmic_basename(images_names[selection[1]].data()),
                  images_names[selection[1]].back()?"*":"",
                  gmic_basename(images_names[selection[2]].data()),
                  images_names[selection[2]].back()?"*":"");
    break;
  case 4:
    cimg_snprintf(res1,sizeof(res1),"%s%s, %s%s, %s%s, %s%s",
                  gmic_basename(images_names[selection[0]].data()),
                  images_names[selection[0]].back()?"*":"",
                  gmic_basename(images_names[selection[1]].data()),
                  images_names[selection[1]].back()?"*":"",
                  gmic_basename(images_names[selection[2]].data()),
                  images_names[selection[2]].back()?"*":"",
                  gmic_basename(images_names[selection[3]].data()),
                  images_names[selection[3]].back()?"*":"");
    break;
  default:
    cimg_snprintf(res1,sizeof(res1),"%s%s, .., %s%s",
                  gmic_basename(images_names[selection[0]].data()),
                  images_names[selection[0]].back()?"*":"",
                  gmic_basename(images_names[selection.back()].data()),
                  images_names[selection.back()].back()?"*":"");
  }
  return res1;
}

#endif // #if defined(gmic_float) || !defined(gmic_split_compilation)

// Print log message.
//-------------------
template<typename T>
gmic& gmic::print(const CImgList<T>& list, const char *format, ...) {
  if (verbosity<0 && !is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  static CImg<char> message(16384);
  cimg_vsnprintf(message,message.width(),format,ap);
  gmic_ellipsize(message,message.width());
  va_end(ap);
  gmic_strreplace(message);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  std::fprintf(cimg::output(),
               "[gmic]-%u%s %s",
               list.size(),scope2string().data(),message.data());
  std::fflush(cimg::output());
  return *this;
}

template<typename T>
gmic& gmic::print(const CImgList<T>& list, const CImg<unsigned int>& scope_selection,
                  const char *format, ...) {
  if (verbosity<0 && !is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  static CImg<char> message(16384);
  cimg_vsnprintf(message,message.width(),format,ap);
  gmic_ellipsize(message,message.width());
  va_end(ap);
  gmic_strreplace(message);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  if (scope_selection)
    std::fprintf(cimg::output(),
                 "[gmic]-%u%s %s",
                 list.size(),scope2string(scope_selection).data(),message.data());
  else std::fprintf(cimg::output(),"%s",message.data());
  std::fflush(cimg::output());
  return *this;
}

// Print warning message.
//-----------------------
template<typename T>
gmic& gmic::warn(const CImgList<T>& list, const char *format, ...) {
  if (verbosity<0 && !is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  static char message[1024+128];
  cimg_snprintf(message,128,"*** Warning in %s *** ",scope2string().data());
  cimg_vsnprintf(message + std::strlen(message),1024,format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  gmic_strreplace(message);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  std::fprintf(cimg::output(),
               "[gmic]-%u%s %s%s%s%s",
               list.size(),scope2string().data(),cimg::t_bold,cimg::t_red,message,cimg::t_normal);
  std::fflush(cimg::output());
  return *this;
}

template<typename T>
gmic& gmic::warn(const CImgList<T>& list, const CImg<unsigned int>& scope_selection,
                 const char *format, ...) {
  if (verbosity<0 && !is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  static char message[1024+128];
  cimg_snprintf(message,128,"*** Warning in %s *** ",scope2string(scope_selection).data());
  cimg_vsnprintf(message + std::strlen(message),1024,format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  gmic_strreplace(message);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  if (scope_selection)
    std::fprintf(cimg::output(),
                 "[gmic]-%u%s %s%s%s%s",
                 list.size(),scope2string(scope_selection).data(),
                 cimg::t_bold,cimg::t_red,message,cimg::t_normal);
  else std::fprintf(cimg::output(),
                    "%s%s%s%s",
                    cimg::t_bold,cimg::t_red,message,cimg::t_normal);
  std::fflush(cimg::output());
  return *this;
}

// Print error message, and quit interpreter.
//-------------------------------------------
template<typename T>
gmic& gmic::error(const CImgList<T>& list, const char *const format, ...) {
  va_list ap;
  va_start(ap,format);
  static char message[1024+128];
  cimg_snprintf(message,128,"*** Error in %s *** ",scope2string().data());
  cimg_vsnprintf(message + std::strlen(message),1024,format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  gmic_strreplace(message);
  CImg<char>::string(message).move_to(status);
  if (verbosity>=0 || is_debug) {
    if (*message!='\r')
      for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
    nb_carriages = 1;
    std::fprintf(cimg::output(),
                 "[gmic]-%u%s %s%s%s%s",
                 list.size(),scope2string().data(),
                 cimg::t_bold,cimg::t_red,message,cimg::t_normal);
    std::fflush(cimg::output());
  }
  throw gmic_exception(0,message);
  return *this;
}

template<typename T>
gmic& gmic::error(const char *const command, const CImgList<T>& list,
                  const char *const format, ...) {
  va_list ap;
  va_start(ap,format);
  static char message[1024+128];
  cimg_snprintf(message,128,"*** Error in %s *** ",scope2string().data());
  cimg_vsnprintf(message + std::strlen(message),1024,format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  gmic_strreplace(message);
  CImg<char>::string(message).move_to(status);
  if (verbosity>=0 || is_debug) {
    if (*message!='\r')
      for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
    nb_carriages = 1;
    std::fprintf(cimg::output(),
                 "[gmic]-%u%s %s%s%s%s",
                 list.size(),scope2string().data(),
                 cimg::t_bold,cimg::t_red,message,cimg::t_normal);
    std::fflush(cimg::output());
  }
  throw gmic_exception(command,message);
  return *this;
}

template<typename T>
gmic& gmic::error(const CImgList<T>& list, const CImg<unsigned int>& scope_selection,
                  const char *const format, ...) {
  va_list ap;
  va_start(ap,format);
  static char message[1024+128];
  cimg_snprintf(message,128,"*** Error in %s *** ",scope2string(scope_selection).data());
  cimg_vsnprintf(message + std::strlen(message),1024,format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  gmic_strreplace(message);
  CImg<char>::string(message).move_to(status);
  if (verbosity>=0 || is_debug) {
    if (*message!='\r')
      for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
    nb_carriages = 1;
    if (scope_selection)
      std::fprintf(cimg::output(),
                   "[gmic]-%u%s %s%s%s%s",
                   list.size(),scope2string(scope_selection).data(),
                   cimg::t_bold,cimg::t_red,message,cimg::t_normal);
    else std::fprintf(cimg::output(),"%s",message);
    std::fflush(cimg::output());
  }
  throw gmic_exception(0,message);
  return *this;
}

// Print bad-argument error message, and quit interpreter.
//--------------------------------------------------------
#define arg_error(command) _arg_error(images,command,argument_text)
template<typename T>
gmic& gmic::_arg_error(const CImgList<T>& list, const char *const command,
                       const char *const argument) {
  static char message[1024];
  cimg_snprintf(message,sizeof(message),
                "*** Error in %s *** Command '%s': Invalid argument '%s'.",
                scope2string().data(),command,argument);
  gmic_ellipsize(message,sizeof(message));
  gmic_strreplace(message);
  CImg<char>::string(message).move_to(status);
  if (verbosity>=0 || is_debug) {
    if (*message!='\r')
      for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
    nb_carriages = 1;
    std::fprintf(cimg::output(),
                 "[gmic]-%u%s %s%s%s%s",
                 list.size(),scope2string().data(),
                 cimg::t_bold,cimg::t_red,message,cimg::t_normal);
    std::fflush(cimg::output());
  }
  throw gmic_exception(command,message);
  return *this;
}

// Print debug message.
//---------------------
template<typename T>
gmic& gmic::debug(const CImgList<T>& list, const char *format, ...) {
  if (!is_debug) return *this;
  va_list ap;
  va_start(ap,format);
  static char message[1024];
  cimg_vsnprintf(message,sizeof(message),format,ap);
  gmic_ellipsize(message,sizeof(message));
  va_end(ap);
  if (*message!='\r')
    for (unsigned int i = 0; i<nb_carriages; ++i) std::fputc('\n',cimg::output());
  nb_carriages = 1;
  std::fprintf(cimg::output(),
               "%s<gmic>-%u%s ",
               cimg::t_green,list.size(),scope2string().data());
  for (char *s = message; *s; ++s) {
    char c = *s;
    if (c<' ') {
      switch (c) {
      case _dollar : std::fprintf(cimg::output(),"\\$"); break;
      case _lbrace : std::fprintf(cimg::output(),"\\{"); break;
      case _rbrace : std::fprintf(cimg::output(),"\\}"); break;
      case _comma : std::fprintf(cimg::output(),"\\,"); break;
      case _dquote : std::fprintf(cimg::output(),"\\\""); break;
      case _arobace : std::fprintf(cimg::output(),"\\@"); break;
      default : std::fputc(c,cimg::output());
      }
    } else std::fputc(c,cimg::output());
  }
  std::fprintf(cimg::output(),
               "%s",
               cimg::t_normal);
  std::fflush(cimg::output());
  return *this;
}

// Remove list of images in a selection.
//---------------------------------------
template<typename T>
gmic& gmic::remove_images(CImgList<T> &images, CImgList<char> &images_names,
                          const CImg<unsigned int>& selection,
                          const unsigned int start, const unsigned int end) {
  if (start==0 && end==(unsigned int)selection.height()-1 && selection.height()==images.width()) {
    images.assign();
    images_names.assign();
  } else for (int l = (int)end; l>=(int)start; ) {
      unsigned int eind = selection[l--], ind = eind;
      while (l>=(int)start && selection[l]==ind-1) ind = selection[l--];
      images.remove(ind,eind); images_names.remove(ind,eind);
    }
  return *this;
}

// Template constructors.
//-----------------------
template<typename T>
gmic::gmic(const int argc, const char *const *const argv,
           CImgList<T>& images,CImgList<char>& images_names,
           const char *custom_commands, const bool include_default_commands,
           float *const p_progress, int *const p_cancel) {
  CImgList<char> items;
  for (int l = 1; l<argc; ++l) {
    if (std::strchr(argv[l],' ')) {
      CImg<char>(1,1,1,1,'\"').move_to(items);
      CImg<char>(argv[l],std::strlen(argv[l])).move_to(items);
      CImg<char>::string("\"").move_to(items);
    } else CImg<char>::string(argv[l]).move_to(items);
    if (l<argc-1) items.back().back()=' ';
  }
  const CImg<char> commands_line(items>'x');
  _gmic(commands_line.data(),images,images_names,custom_commands,include_default_commands,
        p_progress,p_cancel);
}

template<typename T>
gmic::gmic(const char *const commands_line, CImgList<T>& images, CImgList<char>& images_names,
           const char *custom_commands, const bool include_default_commands,
           float *const p_progress, int *const p_cancel) {
  _gmic(commands_line,images,images_names,custom_commands,include_default_commands,
        p_progress,p_cancel);
}

template<typename T>
void gmic::_gmic(const char *const commands_line, CImgList<T>& images,CImgList<char>& images_names,
                 const char *custom_commands, const bool include_default_commands,
                 float *const p_progress, int *const p_cancel) {
  assign(custom_commands,include_default_commands,p_progress,p_cancel);
  const CImgList<char> items = commands_line_to_CImgList(commands_line);
  cimglist_for(items,l) if (!std::strcmp("-debug",items[l].data())) { is_debug = true; break; }
  if (is_debug) {
    debug(images,"%sStart G'MIC instance, in debug mode.%s",cimg::t_bold,cimg::t_normal);
    debug(images,"Initial command line: '%s'.",commands_line);
    is_start = false;
  }
  if (is_debug) commands_line_to_CImgList(commands_line); // Do it twice, when debug enabled.
  try {
    parse(items,images,images_names);
  } catch (gmic_exception &e) {
    print(images,"Abort G'MIC instance.\n");
    throw e;
  }
}

// Print infos on selected images.
//---------------------------------
template<typename T>
gmic& gmic::print_images(const CImgList<T>& images, const CImgList<char>& images_names,
                         const CImg<unsigned int>& selection, const bool is_header) {
  if (!images || !images_names || !selection) {
    if (is_header) print(images,"Print image [].");
    return *this;
  }
  char title[256];
  if (is_header) print(images,"Print image%s.\n",
                       gmic_selection);
  if (verbosity>=0 || is_debug) cimg_forY(selection,l) {
      const unsigned int ind = selection[l];
      cimg_snprintf(title,sizeof(title),"[%u] = '%s'",
                    ind,images_names[ind].data());
      gmic_ellipsize(title,sizeof(title));
      images[ind].gmic_print(title,is_debug);
    }
  nb_carriages = 0;
  return *this;
}

// Display selected images.
//-------------------------
#ifdef gmic_float

template<typename T>
gmic& gmic::display_images(const CImgList<T>& images, const CImgList<char>& images_names,
                           const CImg<unsigned int>& selection, unsigned int *const XYZ) {
  if (!images || !images_names || !selection) { print(images,"Display image []."); return *this; }

  // Check for available display.
#if cimg_display==0
  print(images,"Display image%s",gmic_selection);
  if (verbosity>=0 || is_debug) {
    if (XYZ) std::fprintf(cimg::output(),", from point (%u,%u,%u)",XYZ[0],XYZ[1],XYZ[2]);
    std::fprintf(cimg::output()," (skipped, no display support).");
    std::fflush(cimg::output());
  }
#else // #if cimg_display==0
  bool is_available_display = false;
  try {
    is_available_display = (bool)CImgDisplay::screen_width();
  } catch (CImgDisplayException&) {
    print(images,"Display image%s",gmic_selection);
    if (verbosity>=0 || is_debug) {
      if (XYZ) std::fprintf(cimg::output(),", from point (%u,%u,%u)",XYZ[0],XYZ[1],XYZ[2]);
      std::fprintf(cimg::output()," (skipped, no display available).");
      std::fflush(cimg::output());
    }
  }
  if (!is_available_display) return *this;

  CImgList<T> visu;
  int max_height = 0;
  cimg_forY(selection,l) if (!images[selection(l)].is_CImg3d(false))
    max_height = cimg::max(max_height,images[selection(l)].height());
  cimg_forY(selection,l) {
    const unsigned int ind = selection[l];
    const CImg<T> &img = images[ind];
    if (img) {
      if (!max_height || img.height()<=max_height) visu.insert(img,~0U,true);
      else img.get_rows(0,max_height-1).move_to(visu);
    } else CImg<T>(1,1,1,1,0).move_to(visu);
  }
  const char *const gmic_names = selection2string(selection,images_names,false);
  print(images,"Display image%s = '%s'",gmic_selection,gmic_names);
  if (verbosity>=0 || is_debug) {
    if (XYZ) std::fprintf(cimg::output(),", from point (%u,%u,%u).\n",XYZ[0],XYZ[1],XYZ[2]);
    else std::fprintf(cimg::output(),".\n");
    std::fflush(cimg::output());
  }
  if (visu) {
    CImgDisplay _disp, &disp = instant_window[0]?instant_window[0]:_disp;
    static char title[256];
    if (visu.size()==1)
      cimg_snprintf(title,sizeof(title),"%s (%dx%dx%dx%d)",
                    gmic_names,visu[0].width(),visu[0].height(),visu[0].depth(),visu[0].spectrum());
    else
      cimg_snprintf(title,sizeof(title),"%s (%u)",
                    gmic_names,visu.size());
    gmic_ellipsize(title,sizeof(title));
    CImg<bool> is_shared(visu.size());
    cimglist_for(visu,l) {
      is_shared[l] = visu[l].is_shared();
      visu[l]._is_shared = images[selection[l]].is_shared();
    }
    print_images(images,images_names,selection,false);
    if (disp) visu.display(disp.set_title("%s",title),false,'x',0.5f,XYZ);
    else visu.display(title,false,'x',0.5f,XYZ);
    nb_carriages = 0;
    cimglist_for(visu,l) visu[l]._is_shared = is_shared(l);
  }
#endif // #if cimg_display==0
  return *this;
}

// Display plots of selected images.
//----------------------------------
template<typename T>
gmic& gmic::display_plots(const CImgList<T>& images, const CImgList<char>& images_names,
                          const CImg<unsigned int>& selection,
                          const unsigned int plot_type, const unsigned int vertex_type,
                          const double xmin, const double xmax,
                          const double ymin, const double ymax) {
  if (!images || !images_names || !selection) { print(images,"Plot image []."); return *this; }
#if cimg_display==0
  print(images,"Plot image%s (skipped, no display support).",gmic_selection);
  cimg::unused(plot_type,vertex_type,xmin,xmax,ymin,ymax);
#else // #if cimg_display==0
  bool is_available_display = false;
  try {
    is_available_display = (bool)CImgDisplay::screen_width();
  } catch (CImgDisplayException&) {
    print(images,"Plot image%s (skipped, no display available).",gmic_selection);
  }
  if (!is_available_display) return *this;

  CImgList<unsigned int> empty_indices;
  cimg_forY(selection,l) if (!images[selection(l)])
    CImg<unsigned int>::vector(selection(l)).move_to(empty_indices);
  if (empty_indices) {
    const char *const eselec = selection2string(empty_indices>'y',images_names,true);
    warn(images,"Command 'plot': Image%s %s empty.",
         eselec,empty_indices.size()>1?"are":"is");
  }

  CImgDisplay _disp, &disp = instant_window[0]?instant_window[0]:_disp;
  cimg_forY(selection,l) {
    const unsigned int ind = selection[l];
    const CImg<T>& img = images[ind];
    if (img) {
      print(images,"Plot image%s = '%s'.",gmic_selection,
            selection2string(selection,images_names,false));
      if (verbosity>=0 || is_debug) {
        std::fputc('\n',cimg::output());
        std::fflush(cimg::output());
        img.print(images_names[ind].data());
      }
      if (!disp) disp.assign(cimg_fitscreen(640,480,1),0,0);
      img.display_graph(disp.set_title("%s%s (%dx%dx%dx%d)",
                                       gmic_basename(images_names[ind].data()),
                                       images_names[ind].back()?"*":"",
                                       img.width(),img.height(),img.depth(),img.spectrum()),
                        plot_type,vertex_type,0,xmin,xmax,0,ymin,ymax);
      nb_carriages = 0;
    }
  }
#endif // #if cimg_display==0
  return *this;
}

// Display selected 3d objects.
//-----------------------------
template<typename T>
gmic& gmic::display_objects3d(const CImgList<T>& images, const CImgList<char>& images_names,
                              const CImg<unsigned int>& selection) {
  if (!images || !images_names || !selection) {
    print(images,"Display 3d object [].");
    return *this;
  }
  static char message[1024];
  cimg_forY(selection,l) if (!images[selection[l]].is_CImg3d(true,message))
    error(images,"Command 'display3d': Invalid 3d object [%d] in selected image%s (%s).",
          selection[l],gmic_selection,message);
#if cimg_display==0
  print(images,"Display 3d object%s (skipped, no display support).",gmic_selection);
#else // #if cimg_display==0
  bool is_available_display = false;
  try {
    is_available_display = (bool)CImgDisplay::screen_width();
  } catch (CImgDisplayException&) {
    print(images,"Display 3d object%s (skipped, no display available).",gmic_selection);
  }
  if (!is_available_display) return *this;

  CImgDisplay _disp, &disp = instant_window[0]?instant_window[0]:_disp;
  cimg_forY(selection,l) {
    const unsigned int ind = selection[l];
    const CImg<T> &img = images[ind];
    if (!disp) disp.assign(cimg_fitscreen(640,480,1),0,0);
    CImg<unsigned char> background = background3d.get_resize(disp.width(),disp.height(),1,3);
    background.display(disp);
    CImgList<unsigned int> primitives;
    CImgList<unsigned char> colors;
    CImgList<float> opacities;
    CImg<float> vertices(img,false);
    float _pose3d[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    if (pose3d) std::memcpy(_pose3d,pose3d.data(),16*sizeof(float));
    vertices.CImg3dtoobject3d(primitives,colors,opacities);
    print(images,"Display 3d object [%u] = '%s%s' (%d vertices, %u primitives).",
          ind,images_names[ind].data(),
          images_names[ind].back()?"*":"",
          vertices.width(),primitives.size());
    disp.set_title("%s%s (%d vertices, %u primitives)",
                   gmic_basename(images_names[ind].data()),
                   images_names[ind].back()?"*":"",
                   vertices.width(),primitives.size());
    if (light3d) colors.insert(light3d,~0U,true);
    background.display_object3d(disp,vertices,primitives,colors,opacities,
                                !(bool)pose3d,render3d,renderd3d,is_double3d,focale3d,
                                light3d_x,light3d_y,light3d_z,
                                specular_lightness3d,specular_shininess3d,
                                true,_pose3d);
    print(images,"Selected 3d pose = [ %g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g ].",
          _pose3d[0],_pose3d[1],_pose3d[2],_pose3d[3],
          _pose3d[4],_pose3d[5],_pose3d[6],_pose3d[7],
          _pose3d[8],_pose3d[9],_pose3d[10],_pose3d[11],
          _pose3d[12],_pose3d[13],_pose3d[14],_pose3d[15]);
    if (disp.is_closed()) break;
  }
#endif // #if cimg_display==0
  return *this;
}

#endif // #ifdef gmic_float

// Substitute '@', '{}' and '$' expressions in a string.
//-------------------------------------------------------
template<typename T>
CImg<char> gmic::substitute_item(const char *const source,
                                 CImgList<T>& images,
                                 CImgList<char>& images_names,
                                 const unsigned int (&variables_sizes)[256]) {
  if (!source) return CImg<char>();
  CImgList<char> substituted_items;
  CImg<char> inbraces;
  for (const char *nsource = source; *nsource; )
    if (*nsource!='@' && *nsource!='{' && *nsource!='$') {
      // If not starting with '@', '{', or '$'.
      const char *const nsource0 = nsource;
      do { ++nsource; } while (*nsource && *nsource!='@' && *nsource!='{' && *nsource!='$');
      CImg<char>(nsource0,nsource - nsource0).move_to(substituted_items);
    } else { // '@', '{}' or '$' expression found.
      static CImg<char> substr(256);
      static CImg<unsigned int> _ind;
      if (inbraces) *inbraces = 0; else inbraces.assign(1,1,1,1,0);
      int ind = 0, l_inbraces = 0;
      bool is_braces = false;
      char sep = 0;
      _ind.assign();

      // '{}' expression -> Mathematical evaluation, seq. of ascii codes or strings comparison.
      if (*nsource=='{') {
        const char *const ptr_beg = nsource + 1, *ptr_end = ptr_beg;
        unsigned int p = 0;
        for (p = 1; p>0 && *ptr_end; ++ptr_end) { if (*ptr_end=='{') ++p; if (*ptr_end=='}') --p; }
        if (p) { CImg<char>(nsource++,1).move_to(substituted_items); continue; }
        l_inbraces = ptr_end - ptr_beg - 1;
        if (l_inbraces>0) {
          inbraces.assign(ptr_beg,l_inbraces + 1).back() = 0;
          substitute_item(inbraces,images,images_names,variables_sizes).move_to(inbraces);
          gmic_strreplace(inbraces);
        }
        nsource+=l_inbraces + 2;
        if (*inbraces) {
          const CImg<T> &img = images.size()?images.back():CImg<T>::empty();
          bool is_substitution_done = false;

          // Special regular cases to optimize: {w},{h},{d},{s}.
          if (!inbraces[1]) {
            switch (*inbraces) {
            case 'w' :
              cimg_snprintf(substr,substr.width(),"%d",img.width());
              is_substitution_done = true;
              break;
            case 'h' :
              cimg_snprintf(substr,substr.width(),"%d",img.height());
              is_substitution_done = true;
              break;
            case 'd' :
              cimg_snprintf(substr,substr.width(),"%d",img.depth());
              is_substitution_done = true;
              break;
            case 's' :
              cimg_snprintf(substr,substr.width(),"%d",img.spectrum());
              is_substitution_done = true;
              break;
            }
            if (is_substitution_done)
              CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
          }

          // Sequence of ascii codes.
          if (!is_substitution_done && inbraces.width()>=3 && *inbraces=='\'' &&
              inbraces[inbraces.width()-2]=='\'') {
            const char *s = inbraces.data() + 1;
            if (inbraces.width()>3) {
              inbraces[inbraces.width()-2] = 0;
              for (*substr=0, cimg::strunescape(inbraces); *s; ++s) {
                cimg_snprintf(substr,substr.width(),"%d,",(int)(unsigned char)*s);
                CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
              }
              if (*substr) --(substituted_items.back()._width);
            }
            is_substitution_done = true;
          }

          // Sequence of ascii characters.
          if (!is_substitution_done && inbraces.width()>=3 && *inbraces=='`' &&
              inbraces[inbraces.width()-2]=='`') {
            if (inbraces.width()>3) {
              unsigned int nb_values = 1;
              cimg_for(inbraces,p,char) if (*p==',') ++nb_values;
              inbraces[inbraces.width()-2] = 0;
              try {
                CImg<char>(nb_values,1,1,1,inbraces.data()+1,false).move_to(substituted_items);
                is_substitution_done = true;
              } catch (CImgException &e) {
                const char *const e_ptr = std::strstr(e.what(),": ");
                error(images,"Item substitution '{`value1,..,valueN`}': %s",
                      e_ptr?e_ptr+2:e.what());
              }
            }
            is_substitution_done = true;
          }

          // Strings comparison.
          if (!is_substitution_done && inbraces.width()>=5) {
            char *const peq = std::strstr(inbraces,"'=='");
            if (peq) {
              *peq = 0;
              cimg_snprintf(substr,substr.width(),"%d",(int)!std::strcmp(inbraces,peq+4));
              CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
              is_substitution_done = true;
            } else {
              char *const pne = std::strstr(inbraces,"'!='");
              if (pne) {
                *pne = 0;
                cimg_snprintf(substr,substr.width(),"%d",(int)std::strcmp(inbraces,pne+4));
                CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
                is_substitution_done = true;
              }
            }
          }

          // Mathematical expression [truncated output].
          if (!is_substitution_done && inbraces.width()>=3 && *inbraces=='_') try {
              cimg_snprintf(substr,substr.width(),"%g",img.eval(inbraces.data(1)));
              CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
              is_substitution_done = true;
            } catch (CImgException& e) {
              const char *const e_ptr = std::strstr(e.what(),": ");
              error(images,"Item substitution '{_expression}': %s",
                    e_ptr?e_ptr+2:e.what());
            }

          // Mathematical expression [full precision output].
          if (!is_substitution_done) try {
              cimg_snprintf(substr,substr.width(),"%.16g",img.eval(inbraces.data()));
              CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
            } catch (CImgException& e) {
              const char *const e_ptr = std::strstr(e.what(),": ");
              error(images,"Item substitution '{expression}': %s",
                    e_ptr?e_ptr+2:e.what());
            }
        }
        continue;

        // '@{..}' and ${..} expressions.
      } else if (nsource[1]=='{') {
        const char *const ptr_beg = nsource + 2, *ptr_end = ptr_beg; unsigned int p = 0;
        for (p = 1; p>0 && *ptr_end; ++ptr_end) { if (*ptr_end=='{') ++p; if (*ptr_end=='}') --p; }
        if (p) { CImg<char>(nsource++,1).move_to(substituted_items); continue; }
        l_inbraces = ptr_end - ptr_beg - 1;
        if (l_inbraces>0) {
          inbraces.assign(ptr_beg,l_inbraces + 1).back() = 0;
          substitute_item(inbraces,images,images_names,variables_sizes).move_to(inbraces);
        }
        is_braces = true;
      }

      // Substitute '@#' -> number of images in the list.
      if (*nsource=='@' && nsource[1]=='#') {
        nsource+=2;
        cimg_snprintf(substr,substr.width(),"%u",images.size());
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@.' -> current version number of the G'MIC interpreter.
      } else if (*nsource=='@' && nsource[1]=='.') {
        nsource+=2;
        cimg_snprintf(substr,substr.width(),"%u",gmic_version);
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@%' -> pid of the current process.
      } else if (*nsource=='@' && nsource[1]=='%') {
        nsource+=2;
#if cimg_OS==1
        cimg_snprintf(substr,substr.width(),"%u",(unsigned int)getpid());
#elif cimg_OS==2
        cimg_snprintf(substr,substr.width(),"%u",(unsigned int)_getpid());
#else // #if cimg_OS==1
        cimg_snprintf(substr,substr.width(),"0");
#endif // #if cimg_OS==1
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@|' -> current value of the timer.
      } else if (*nsource=='@' && nsource[1]=='|') {
        static const unsigned long t0 = cimg::time();
        nsource+=2;
        cimg_snprintf(substr,substr.width(),"%g",(cimg::time()-t0)/1000.);
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@?' -> current type of image pixels.
      } else if (*nsource=='@' && nsource[1]=='?') {
        nsource+=2;
        cimg_snprintf(substr,substr.width(),"%s",CImg<T>::pixel_type());
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@!' -> visibility state of the first instant display window.
      } else if (*nsource=='@' && nsource[1]=='!') {
        nsource+=2;
#if cimg_display==0
        std::strcpy(substr,"0");
#else // #if cimg_display==0
        cimg_snprintf(substr,substr.width(),"%d",
                      instant_window[0]?(instant_window[0].is_closed()?0:1):0);
#endif // #if cimg_display==0
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@{!}', @{!1}, '@{!,subset}' and '@{!1,subset}'
        // -> features of an instant display window.
      } else if (*nsource=='@' && inbraces[0]=='!' &&
                 (inbraces[1]==0 ||
                  (inbraces[1]>='0' && inbraces[1]<='9' && inbraces[2]==0) ||
                  (inbraces[1]==',' && inbraces[2]) ||
                  (inbraces[1]>='0' && inbraces[1]<='9' && inbraces[2]==',' && inbraces[3]))) {
        nsource+=l_inbraces + 3;
#if cimg_display==0
        std::strcpy(substr,"0");
#else // #if cimg_display==0
        unsigned int wind = 0;
        bool is_substitution_done = true;
        const char *ninbraces = inbraces.data() + 1;
        if (*ninbraces>='0' && *ninbraces<='9') wind = (unsigned int)(*(ninbraces++)-'0');
        if (!*ninbraces)
          cimg_snprintf(substr,substr.width(),"%d",
                        instant_window[wind]?(instant_window[wind].is_closed()?0:1):0);
        else if (*ninbraces==',') switch (*(++ninbraces)) {
          case 'w' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].width());
            else if (ninbraces[1]=='h' && !ninbraces[2])
              cimg_snprintf(substr,substr.width(),"%d",
                            instant_window[wind].width()*instant_window[wind].height());
            else is_substitution_done = false;
            break;
          case 'h' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].height());
            else is_substitution_done = false;
            break;
          case 'd' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].window_width());
            else if (ninbraces[1]=='e' && !ninbraces[2])
              cimg_snprintf(substr,substr.width(),"%d",
                            instant_window[wind].window_width()*
                            instant_window[wind].window_height());
            else is_substitution_done = false;
            break;
          case 'e' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].window_height());
            else is_substitution_done = false;
            break;
          case 'u' :
            if (!ninbraces[1]) try {
                cimg_snprintf(substr,substr.width(),"%d",CImgDisplay::screen_width());
              } catch (CImgDisplayException&) { std::strcpy(substr,"0"); }
            else if (ninbraces[1]=='v' && !ninbraces[2]) try {
                cimg_snprintf(substr,substr.width(),"%d",
                              CImgDisplay::screen_width()*CImgDisplay::screen_height());
              } catch (CImgDisplayException&) { std::strcpy(substr,"0"); }
            else is_substitution_done = false;
            break;
          case 'v' :
            if (!ninbraces[1]) try {
                cimg_snprintf(substr,substr.width(),"%d",CImgDisplay::screen_height());
              } catch (CImgDisplayException&) { std::strcpy(substr,"0"); }
            else is_substitution_done = false;
            break;
          case 'x' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].mouse_x());
            else is_substitution_done = false;
            break;
          case 'y' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].mouse_y());
            else is_substitution_done = false;
            break;
          case 'n' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].normalization());
            else is_substitution_done = false;
            break;
          case 'b' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].button());
            else is_substitution_done = false;
            break;
          case 'o' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].wheel());
            else is_substitution_done = false;
            break;
          case 'c' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",(int)instant_window[wind].is_closed());
            else is_substitution_done = false;
            break;
          case 'r' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",(int)instant_window[wind].is_resized());
            else is_substitution_done = false;
            break;
          case 'm' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%d",(int)instant_window[wind].is_moved());
            else is_substitution_done = false;
            break;
          case 'k' :
            if (!ninbraces[1])
              cimg_snprintf(substr,substr.width(),"%u",instant_window[wind].key());
            else is_substitution_done = false;
            break;
          default :
            cimg_snprintf(substr,substr.width(),"%d",instant_window[wind].is_key(ninbraces));
          } else cimg_snprintf(substr,substr.width(),"@{!%s}",inbraces.data());
        if (!is_substitution_done) std::strcpy(substr,"0");
#endif // #if cimg_display==0
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@/' -> number of levels in current global scope.
      } else if (*nsource=='@' && nsource[1]=='/') {
        nsource+=2;
        cimg_snprintf(substr,substr.width(),"%u",scope.size());
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@{/}' and '@{/,subset}' -> content of the global scope.
      } else if (*nsource=='@' && inbraces[0]=='/' &&
                 (inbraces[1]==0 || (inbraces[1]==',' && inbraces[2]))) {
        nsource+=l_inbraces + 3;
        const CImg<unsigned int>
          subset = selection2cimg(inbraces[1]?inbraces.data()+2:0,scope.size(),
                                  CImgList<char>::empty(),
                                  "Item substitution '@{/[,subset]}'",false,
                                  false,CImg<char>::empty());
        if (subset) cimg_foroff(subset,i)
                      substituted_items.insert(scope[subset[i]]).back().back() = '/';

        // Substitute '$/' -> name of the current command.
      } else if (*nsource=='$' && nsource[1]=='/') {
        cimg_snprintf(substr,substr.width(),"%s",scope.back().data());
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
        nsource+=2;

        // Substitute '@>' and '@<' -> current number of nested loops.
      } else if (*nsource=='@' && (nsource[1]=='>' || nsource[1]=='<')) {
        nsource+=2;
        cimg_snprintf(substr,substr.width(),"%u",repeatdones.size());
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

        // Substitute '@{>}', '@{<}', '@{>,subset}' and '@{<,subset}'
        // -> forward/backward indice(s) of current loop(s).
      } else if (*nsource=='@' && (*inbraces=='>' || *inbraces=='<') &&
                 (inbraces[1]==0 || (inbraces[1]==',' && inbraces[2]))) {
        nsource+=l_inbraces + 3;
        const CImg<unsigned int>
          subset = selection2cimg(inbraces[1]?inbraces.data()+2:0,repeatdones.size(),
                                  CImgList<char>::empty(),
                                  "Item substitution '@{>[,subset]}'",false,
                                  false,CImg<char>::empty());
        if (subset) {
          cimg_foroff(subset,i) {
            cimg_snprintf(substr,substr.width(),"%u",
                          *inbraces=='>'?repeatdones(subset[i],2):repeatdones(subset[i],1)-1);
            CImg<char>::string(substr.data()).move_to(substituted_items).back().back()=',';
          }
          --(substituted_items.back()._width);
        }

        // Substitute '$>', '${>}', '$<' and '${<}' -> forward/backward indice of current loop.
      } else if (*nsource=='$' &&
                 (nsource[1]=='>' || nsource[1]=='<' ||
                  ((*inbraces=='>' || *inbraces=='<') && inbraces[1]==0))) {
        const char direction = is_braces?*inbraces:nsource[1];
        if (!repeatdones)
          error(images,"Item substitution '$%s': There is no loop currently running.",
                is_braces?(direction=='>'?"{>}":"{<}"):(direction=='>'?">":"<"));
        cimg_snprintf(substr,substr.width(),"%u",
                      direction=='>'?repeatdones.back()(2):repeatdones.back()(1)-1);
        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
        nsource+=is_braces?4:2;

        // Substitute '$name' and '${name}' -> variable, image indice or environment variable.
      } else if (*nsource=='$' &&
                 (((is_braces && std::sscanf(inbraces,"%255[a-zA-Z0-9_]",substr.data())==1)) ||
                  (std::sscanf(nsource+1,"%255[a-zA-Z0-9_]",substr.data())==1)) &&
                 (*substr<'0' || *substr>'9')) {
        const CImg<char>& name = is_braces?inbraces:substr;
        const unsigned int sind = gmic_hashcode(name,true);
        const int lind = *name=='_'?0:(int)variables_sizes[sind];
        const CImgList<char>
          &_variables = variables[sind],
          &_variables_names = variables_names[sind];
        bool is_name_found = false;
        for (int l = _variables.width()-1; l>=lind; --l)
          if (!std::strcmp(_variables_names[l],name)) {
            is_name_found = true; ind = l; break;
          }
        if (is_name_found) {
          if (_variables[ind].size()>1)
            CImg<char>(_variables[ind].data(),_variables[ind].size()-1).
              move_to(substituted_items);
        } else {
          for (int l = images.width()-1; l>=0; --l)
            if (images_names[l] && !std::strcmp(images_names[l],name)) {
              is_name_found = true; ind = l; break;
            }
          if (is_name_found) {
            char text[64];
            cimg_snprintf(text,sizeof(text),"%d",ind);
            CImg<char>(text,std::strlen(text)).move_to(substituted_items);
          } else {
            const char *const s_env = std::getenv(name);
            if (s_env) CImg<char>(s_env,std::strlen(s_env)).move_to(substituted_items);
          }
        }
        nsource+=is_braces?l_inbraces + 3:std::strlen(substr)+1;

        // Substitute '@ind', '@{ind}' and '@{ind,argument}' -> image values or feature.
      } else if (*nsource=='@' && (std::sscanf(nsource+1,"%d",&ind)==1 ||
                                   ((end=0),std::sscanf(inbraces,"%d%c",&ind,&end)==1) ||
                                   ((end=1),std::sscanf(inbraces,"%d,%c",&ind,&sep)==2) ||
                                   (std::sscanf(nsource+1,"%255[a-zA-Z0-9_]",substr.data())==1 &&
                                    (_ind=selection2cimg(substr,images.size(),images_names,
                                                         "Item substitution '@name'",true,
                                                         false,CImg<char>::empty())).height()>0) ||
                                   (((end=0),std::sscanf(inbraces,"%255[a-zA-Z0-9_]%c",
                                                         substr.data(),&end)==1) &&
                                    (_ind=selection2cimg(substr,images.size(),images_names,
                                                         "Item substitution '@{name}'",true,
                                                         false,CImg<char>::empty())).height()>0) ||
                                   (((end=1),std::sscanf(inbraces,"%255[a-zA-Z0-9_],%c",
                                                         substr.data(),&sep)==2) &&
                                    (_ind=selection2cimg(substr,images.size(),images_names,
                                                         "Item substitution '@{name,feature}'",
                                                         true,false,
                                                         CImg<char>::empty())).height()>0))) {
        if (_ind) {
          if (_ind.height()>1)
            error(images,"Item substitution '%s': Selection [%s] specifies %d items.",
                  !*inbraces?"@name":end?"@{name,feature}":"@{name}",
                  substr.data(),_ind.height());
          ind=*_ind;
        }
        const unsigned int
          l_ind = _ind?std::strlen(substr):cimg_snprintf(substr,substr.width(),"%d",ind);
        nsource+=is_braces?l_inbraces + 3:l_ind + 1;
        int nind = ind;
        if (nind<0) nind+=images.width();
        if (nind<0 || nind>=images.width()) {
          if (images.width())
            error(images,"Item substitution '%s': Invalid indice '%d' (not in range -%u..%u).",
                  !*inbraces?"@indice":end?"@{indice,feature}":"@{indice}",
                  ind,images.size(),images.size()-1);
          else
            error(images,"Item substitution '%s': Invalid indice '%d' (no image data available).",
                  !*inbraces?"@indice":end?"@{indice,feature}":"@{indice}",ind);
        }
        const CImg<T>& img = images[nind];
        static char argx[256], argy[256], argz[256], argc[256];
        *argx = *argy = *argz = *argc = 0;
        char sepp = 0, sepx = 0, sepy = 0, sepz = 0, sepc = 0;
        float x = 0, y = 0, z = 0, v = 0, bcond = 0;
        bool is_substitution_done = false;
        const char *subset = sep?inbraces.data() + l_ind + 1:&sep;
        *substr = 0;

        // Test for simple arguments '@{ind,arg}' where 'arg' is w,h,d,s,....
        if (*subset) {
          is_substitution_done = true;
          switch (*subset) {
          case 'w' :
            if (subset[1]=='h') {
              if (subset[2]=='d') {
                if (subset[3]=='s' && !subset[4])
                  cimg_snprintf(substr,substr.width(),"%d",
                                img.width()*img.height()*img.depth()*img.spectrum());
                else if (!subset[3])
                  cimg_snprintf(substr,substr.width(),"%d",
                                img.width()*img.height()*img.depth());
                else is_substitution_done = false;
              } else if (!subset[2])
                cimg_snprintf(substr,substr.width(),"%d",img.width()*img.height());
              else is_substitution_done = false;
            } else if (!subset[1])
              cimg_snprintf(substr,substr.width(),"%d",img.width());
            else is_substitution_done = false;
            break;
          case 'h' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%d",img.height());
            else is_substitution_done = false;
            break;
          case 'd' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%d",img.depth());
            else is_substitution_done = false;
            break;
          case 's' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%d",img.spectrum());
            else is_substitution_done = false;
            break;
          case 'r' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%d",img.is_shared());
            else is_substitution_done = false;
            break;
          case 'n' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%s",images_names[nind].data());
            else is_substitution_done = false;
            break;
          case 'b' :
            if (!subset[1]) {
              cimg::split_filename(images_names[nind].data(),substr);
              const char *const basename = cimg::basename(substr);
              if (substr.data()!=basename) std::strcpy(substr,basename);
            } else is_substitution_done = false;
            break;
          case 'x' :
            if (!subset[1])
              cimg_snprintf(substr,substr.width(),"%s",
                            cimg::split_filename(images_names[nind].data()));
            else is_substitution_done = false;
            break;
          case 'f' :
            if (!subset[1]) {
              CImg<char> _substr(images_names[nind]);
              char *const basename = const_cast<char*>(cimg::basename(_substr));
              *basename = 0;
              std::strcpy(substr,_substr);
            } else is_substitution_done = false;
            break;
          case '#' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%lu",img.size());
            else is_substitution_done = false;
            break;
          case '+' :
            if (!subset[1]) {
              double res = img?(double)img.front():0;
              for (const T *ptrs = img.data() + 1, *ptre = img.end(); ptrs<ptre;
                   res+=(double)*ptrs++) {}
              cimg_snprintf(substr,substr.width(),"%.16g",res);
            } else is_substitution_done = false;
            break;
          case '-' :
            if (!subset[1]) {
              double res = img?(double)img.front():0;
              for (const T *ptrs = img.data() + 1, *ptre = img.end(); ptrs<ptre;
                   res-=(double)*ptrs++) {}
              cimg_snprintf(substr,substr.width(),"%.16g",res);
            } else is_substitution_done = false;
            break;
          case '*' :
            if (!subset[1]) {
              double res = img?(double)img.front():0;
              for (const T *ptrs = img.data() + 1, *ptre = img.end(); ptrs<ptre;
                   res*=(double)*ptrs++) {}
              cimg_snprintf(substr,substr.width(),"%.16g",res);
            } else is_substitution_done = false;
            break;
          case '/' : if (!subset[1]) {
              double res = img?(double)img.front():0;
              for (const T *ptrs = img.data() + 1, *ptre = img.end(); ptrs<ptre;
                   res/=(double)*ptrs++) {}
              cimg_snprintf(substr,substr.width(),"%.16g",res);
            } else is_substitution_done = false;
            break;
          case 'm' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%.16g",(double)img.min());
            else is_substitution_done = false;
            break;
          case 'M' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%.16g",(double)img.max());
            else is_substitution_done = false;
            break;
          case 'a' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%.16g",img.mean());
            else is_substitution_done = false;
            break;
          case 'v' :
            if (!subset[1]) cimg_snprintf(substr,substr.width(),"%.16g",img.variance());
            else is_substitution_done = false;
            break;
          case 't' :
            if (!subset[1]) {
              const unsigned int siz = (unsigned int)img.size();
              if (siz) {
                CImg<char> text(siz+1), _text = text.get_shared_points(0,siz-1,0,0,0);
                _text = CImg<T>(img.data(),siz,1,1,1,true);
                text.back() = 0;
                gmic_strreplace(text.data());
                _text.move_to(substituted_items);
              }
              *substr = 0;
            } else is_substitution_done = false;
            break;
          case 'c' :
            if (!subset[1]) {
              CImg<unsigned int> st;
              if (img) st = img.get_stats(); else st.assign(8,1,1,1,0);
              cimg_snprintf(substr,substr.width(),"%u,%u,%u,%u",st[4],st[5],st[6],st[7]);
            } else is_substitution_done = false;
            break;
          case 'C' :
            if (!subset[1]) {
              CImg<unsigned int> st;
              if (img) st = img.get_stats(); else st.assign(12,1,1,1,0);
              cimg_snprintf(substr,substr.width(),"%u,%u,%u,%u",st[8],st[9],st[10],st[11]);
            } else is_substitution_done = false;
            break;
          default : is_substitution_done = false;
          }

          // Test for access to pixel value '@{ind,(x,y,z,c,boundary)}'.
          if (is_substitution_done) {
            if (*substr) CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
          } else if ((std::sscanf(subset,"(%255[0-9.eE%+-]%c%c",
                                  argx,&sepp,&end)==2 ||
                      std::sscanf(subset,"(%255[0-9.eE%+-],%255[0-9.eE%+-]%c%c",
                                  argx,argy,&sepp,&end)==3 ||
                      std::sscanf(subset,"(%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c%c",
                                  argx,argy,argz,&sepp,&end)==4 ||
                      std::sscanf(subset,"(%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                  "%255[0-9.eE%+-]%c%c",
                                  argx,argy,argz,argc,&sepp,&end)==5 ||
                      std::sscanf(subset,"(%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                  "%255[0-9.eE%+-],%f%c%c",
                                  argx,argy,argz,argc,&bcond,&sepp,&end)==6) &&
                     sepp==')' &&
                     (std::sscanf(argx,"%f%c",&x,&end)==1 ||
                      (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                     (!*argy ||
                      std::sscanf(argy,"%f%c",&y,&end)==1 ||
                      (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                     (!*argz ||
                      std::sscanf(argz,"%f%c",&z,&end)==1 ||
                      (std::sscanf(argz,"%f%c%c",&z,&sepz,&end)==2 && sepz=='%')) &&
                     (!*argc ||
                      std::sscanf(argc,"%f%c",&v,&end)==1 ||
                      (std::sscanf(argc,"%f%c%c",&v,&sepc,&end)==2 && sepc=='%'))) {
            const int
              nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
              ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y),
              nz = (int)cimg::round(sepz=='%'?z*(img.depth()-1)/100:z),
              nv = (int)cimg::round(sepc=='%'?v*(img.spectrum()-1)/100:v);
            cimg_snprintf(substr,substr.width(),"%.16g",
                          bcond?(double)img.atXYZC(nx,ny,nz,nv):(double)img.atXYZC(nx,ny,nz,nv,0));
            CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
            is_substitution_done = true;
          }
        }

        // Test for values subset, as in '@{ind,0-10}'.
        if (!is_substitution_done) {
          CImg<T> values;
          is_substitution_done = true;
          if (!*subset) values = img.get_shared();
          else {
            int _verbosity = verbosity;
            bool _is_debug = is_debug;
            verbosity = -1; is_debug = false;
            try {
              const CImg<unsigned int>
                inds = selection2cimg(subset,img.size(),
                                      CImgList<char>::empty(),"",false,false,CImg<char>::empty());
              values.assign(1,inds.height());
              cimg_foroff(inds,p) values[p] = img[inds(p)];
            } catch (gmic_exception&) {
              is_substitution_done = false;
            }
            verbosity = _verbosity; is_debug = _is_debug;
          }
          if (is_substitution_done) {
            cimg_foroff(values,p) {
              cimg_snprintf(substr,substr.width(),"%.16g",(double)values[p]);
              CImg<char>::string(substr).move_to(substituted_items).back().back() = ',';
            }
            if (values) --(substituted_items.back()._width);
          }
        }

        // -> 'argument' is considered as math expression associated to an image, as '@{ind,w/2}'.
        if (!is_substitution_done) {
          try {
            cimg_snprintf(substr,substr.width(),"%.16g",img.eval(subset));
          } catch (CImgException&) {
            error(images,"Item substitution '@{%d,%s}': Invalid argument '%s'.",
                  ind,subset,subset);
          }
          CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
        }

        // Substitute '@' by itself, if no @-pattern matches.
      } else if (!is_braces || *nsource!='@') CImg<char>(nsource++,1).move_to(substituted_items);

      // Substitute '@{command}' by the status value after command execution.
      else {
        nsource+=l_inbraces + 3;
        if (l_inbraces>0) {
          const CImgList<char>
            ncommands_line = commands_line_to_CImgList(gmic_strreplace(inbraces));
          unsigned int nposition = 0;
          CImg<char>::string("*substitute").move_to(scope);
          unsigned int nvariables_sizes[256];
          for (unsigned int l = 0; l<256; ++l) nvariables_sizes[l] = variables[l].size();
          --verbosity;
          try { parse(ncommands_line,nposition,images,images_names,nvariables_sizes); }
          catch (...) { ++verbosity; throw; }
          ++verbosity;
          for (unsigned int l = 0; l<255; ++l) if (variables[l].size()>nvariables_sizes[l]) {
              variables_names[l].remove(nvariables_sizes[l],variables[l].size()-1);
              variables[l].remove(nvariables_sizes[l],variables[l].size()-1);
            }
          scope.remove();
          is_return = false;
        }
        if (status.width()>1)
          CImg<char>(status.data(),status.width()-1).move_to(substituted_items);
        continue;
      }
    }
  CImg<char>::vector(0).move_to(substituted_items);
  return substituted_items>'x';
}

// Main parsing procedure.
//------------------------
template<typename T>
gmic& gmic::parse(const CImgList<char>& commands_line, unsigned int& position,
                  CImgList<T> &images, CImgList<char> &images_names,
                  const unsigned int (&variables_sizes)[256]) {
  const unsigned int initial_scope_size = scope.size();
  bool is_endlocal = false;
  try {

    // Init parser environment.
    cimg::exception_mode() = 0;
    if (images.size()<images_names.size())
      images_names.remove(images.size(),images_names.size()-1);
    else if (images.size()>images_names.size())
      images_names.insert(images.size() - images_names.size(),CImg<char>::string("[unnamed]"));
    if (is_debug) {
      nb_carriages = 2;
      debug(images,"%sStart G'MIC parser in scope '%s/' [%s]:%s",
            cimg::t_bold,scope.back().data(),CImg<T>::pixel_type(),cimg::t_normal);
      is_start = false;
    }

    // Begin command line parsing.
    if (!commands_line && is_start) { print(images,"Start G'MIC parser."); is_start = false; }
    while (position<commands_line.size() && !is_quit && !is_return) {
      const char
        *const initial_item = commands_line[position].data(),
        *const initial_argument = position+1<commands_line.size()?commands_line[position+1].data():"";

      // Allocate relatively big static variables, widely used afterwards
      // (prevents stack overflow on recursive calls).
      static char formula[4096], message[1024], title[256], indices[256],
        argx[256], argy[256], argz[256], argc[256];
#ifdef gmic_float
      static char color[4096];
#endif // #ifdef gmic_float

      // Check consistency of the parser environment.
      if (images_names.size()!=images.size())
        error("Internal error: Images (%u) and images names (%u) have different size.",
              images_names.size(),images.size());
      if (!scope)
        error("Internal error: Scope is empty.");
      if (scope.size()>256)
        error("Internal error: Scope overflow (infinite recursion ?).");

      // Substitute expressions in current item.
      CImg<char> _item, _argument, _argument_text;
      substitute_item(initial_item,images,images_names,variables_sizes).move_to(_item);
      char *item = _item.data();
      const char *argument = initial_argument, *argument_text = initial_argument;

      // Split command/restriction, if necessary.
      static char command[256], restriction[256];
      *command = *restriction = 0;
      bool is_get_version = false, is_restriction = false;
      CImg<unsigned int> selection;
      CImg<char> new_name;
      if (item[0]=='-' && item[1] && item[1]!='.') {
        char sep0 = 0, sep1 = 0;
        if (item[1]=='-' && item[2] && item[2]!='[' && (item[2]!='3' || item[3]!='d')) {
          ++item; is_get_version = true;
        }
        gmic_strreplace(item);
        const int err = std::sscanf(item,"%255[^[]%c%255[a-zA-Z_0-9.eE%^,:+-]%c%c",
                                    command,&sep0,restriction,&sep1,&end);
        if (err==1) selection = CImg<unsigned int>::sequence(images.size(),0,images.size()-1);
        else if (err==2 && sep0=='[' && item[std::strlen(command)+1]==']') {
          selection.assign(); is_restriction = true;
        } else if (err==4 && sep1==']') {
          is_restriction = true;
          if (!std::strcmp("-wait",command))
            selection = selection2cimg(restriction,10,CImgList<char>::empty(),command,true,
                                       false,CImg<char>::empty());
          else if (!std::strcmp("-input",command) || !std::strcmp("-i",command))
            selection = selection2cimg(restriction,images.size()+1,images_names,command,true,
                                       true,new_name);
          else if (!std::strcmp("-echo",command) || !std::strcmp("-e",command) ||
                   !std::strcmp("-error",command) || !std::strcmp("-warn",command))
            selection = selection2cimg(restriction,scope.size(),CImgList<char>::empty(),
                                       command,true,false,CImg<char>::empty());
          else
            selection = selection2cimg(restriction,images.size(),images_names,command,true,
                                       false,CImg<char>::empty());
        } else {
          std::strncpy(command,item,sizeof(command)-1);
          command[sizeof(command)-1] = *restriction = 0;
        }
        if (is_get_version) --item;
      } else {
        std::strncpy(command,item,sizeof(command)-1);
        command[sizeof(command)-1] = *restriction = 0;
      }
      ++position;

      if (is_debug) {
        const char *const _initial_item = initial_item+(is_get_version?1:0);
        if (std::strcmp(item,_initial_item))
          debug(images,"Item '%s' -> '%s', indice%s.",
                _initial_item,item,gmic_selection);
        else
          debug(images,"Item '%s', indice%s.",
                _initial_item,gmic_selection);
      }

      // Check for verbosity command, prior to the first output of a log message.
      if (!std::strcmp("-verbose",item) || !std::strcmp("-v",item)) {
        gmic_substitute_args();
        float level = 0;
        if (std::sscanf(argument,"%f%c",&level,&end)==1) verbosity = (int)cimg::round(level);
        else if (*argument=='+' && !argument[1]) ++verbosity;
        else if (*argument=='-' && !argument[1]) --verbosity;
        else {
          if (is_start) { print(images,"Start G'MIC parser."); is_start = false; }
          arg_error("verbose");
        }
      }
      if (is_start) { print(images,"Start G'MIC parser."); is_start = false; }

      // Begin command interpretation.
      if (*item=='-' && item[1]) {

        // Replace some shortcut names whose three first chars are different than correspondent
        // regular names (not all shortcuts are replaced, but it reduces the number of string
        // comparisons afterwards).
        static char _item[16] = { 0 };
        char command1 = command[1];
        const char
          command2 = command1?command[2]:0, command3 = command2?command[3]:0,
          command4 = command3?command[4]:0, command5 = command4?command[5]:0;

        if (!command2) switch (command1) {  // One-char shortcuts.
          case 'm' : if (!is_get_version) { std::strcpy(item=_item,"-command"); command1 = 'c'; }
            break;
          case 'd' : std::strcpy(command,"-display"); break;
          case 'e' : std::strcpy(command,"-echo"); break;
          case 'i' : std::strcpy(command,"-input"); break;
          case 'o' : std::strcpy(command,"-output"); break;
          case 'p' : std::strcpy(command,"-print"); break;
          case 'v' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-verbose"); break;
          case 'w' : std::strcpy(command,"-window"); break;
          case 'k' : std::strcpy(command,"-keep"); break;
          case '+' : std::strcpy(command,"-add"); command1 = 'a'; break;
          case '/' : std::strcpy(command,"-div"); command1 = 'd'; break;
          case '>' : std::strcpy(command,"-gt"); command1 = 'g'; break;
          case '<' : std::strcpy(command,"-lt"); command1 = 'l'; break;
          case '%' : std::strcpy(command,"-mod"); command1 = 'm'; break;
          case '*' : std::strcpy(command,"-mul"); command1 = 'm'; break;
          case '^' : std::strcpy(command,"-pow"); command1 = 'p'; break;
          case '-' : std::strcpy(command,"-sub"); command1 = 's'; break;
          case 'c' : std::strcpy(command,"-cut"); break;
          case 'f' : std::strcpy(command,"-fill"); break;
          case 'n' : std::strcpy(command,"-normalize"); break;
          case '=' : std::strcpy(command,"-set"); command1 = 's'; break;
          case 't' : std::strcpy(command,"-text"); break;
          case 'a' : std::strcpy(command,"-append"); break;
          case 'z' : std::strcpy(command,"-crop"); command1 = 'c'; break;
          case 'r' : std::strcpy(command,"-resize"); break;
          case 's' : std::strcpy(command,"-split"); break;
          case 'y' : std::strcpy(command,"-unroll"); command1 = 'u'; break;
          case 'b' : std::strcpy(command,"-blur"); break;
          case 'g' : std::strcpy(command,"-gradient"); break;
          case 'j' : std::strcpy(command,"-image"); command1 = 'i'; break;
          case 'q' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-quit"); break;
          case 'l' : std::strcpy(command,"-local"); break;
          case 'u' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-status"); command1 = 's'; break;
          case 'x' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-exec"); command1 = 'e'; break;
          } else if (!command3) { // Two-chars shortcuts.
          if (command1=='s' && command2=='h') std::strcpy(command,"-shared");
          else if (command1=='m' && command2=='v') std::strcpy(command,"-move");
          else if (command1=='n' && command2=='m') std::strcpy(command,"-name");
          else if (command1=='r' && command2=='m') std::strcpy(command,"-remove");
          else if (command1=='r' && command2=='v') std::strcpy(command,"-reverse");
          else if (command1=='<' && command2=='<') { std::strcpy(command,"-bsl"); command1 = 'b'; }
          else if (command1=='>' && command2=='>') { std::strcpy(command,"-bsr"); command1 = 'b'; }
          else if (command1=='=' && command2=='=') { std::strcpy(command,"-eq"); command1 = 'e'; }
          else if (command1=='>' && command2=='=') { std::strcpy(command,"-ge"); command1 = 'g'; }
          else if (command1=='<' && command2=='=') { std::strcpy(command,"-le"); command1 = 'l'; }
          else if (command1=='/' && command2=='/') {
            std::strcpy(command,"-mdiv"); command1 = 'm';
          }
          else if (command1=='*' && command2=='*') {
            std::strcpy(command,"-mmul"); command1 = 'm';
          }
          else if (command1=='!' && command2=='=') { std::strcpy(command,"-neq"); command1 = 'n'; }
        } else if (!command4 && command2=='3' && command3=='d') switch (command1) {
            // Three-chars shortcuts (ending with '3d').
          case 'd' : std::strcpy(command,"-display3d"); break;
          case '+' : std::strcpy(command,"-add3d"); command1 = 'a'; break;
          case 'b' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-background3d"); break;
          case '/' : std::strcpy(command,"-div3d"); command1 = 'd'; break;
          case 'f' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-focale3d"); break;
          case 'l' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-light3d"); break;
          case 'm' : if (!is_get_version && !is_restriction)
              std::strcpy(item=_item,"-mode3d"); break;
          case '*' : std::strcpy(command,"-mul3d"); command1 = 'm'; break;
          case 'o' : std::strcpy(command,"-opacity3d"); break;
          case 'p' : std::strcpy(command,"-primitives3d"); break;
          case 'r' : std::strcpy(command,"-rotate3d"); break;
          case 's' : std::strcpy(command,"-split3d"); break;
          case '-' : std::strcpy(command,"-sub3d"); command1 = 's'; break;
          case 't' : std::strcpy(command,"-texturize3d"); break;
          } else if (!command5 && command3=='3' && command4=='d') {
          // Four-chars shortcuts (ending with '3d').
          if (command1=='d' && command2=='b') {
            if (!is_get_version && !is_restriction) std::strcpy(item=_item,"-double3d");
          } else if (command1=='m' && command2=='d') {
            if (!is_get_version && !is_restriction) std::strcpy(item=_item,"-moded3d");
          }
          else if (command1=='r' && command2=='v') std::strcpy(command,"-reverse3d");
          else if (command1=='s' && command2=='l') {
            if (!is_get_version && !is_restriction) std::strcpy(item=_item,"-specl3d");
          }
          else if (command1=='s' && command2=='s') {
            if (!is_get_version && !is_restriction) std::strcpy(item=_item,"-specs3d");
          }
        }

        // Check if new name has been requested for a command that does not allow that.
        if (new_name && std::strcmp("-input",command))
          error(images,"Item '%s %s': Unknow name '%s'.",
                initial_item,initial_argument,new_name.data());

        //----------------------------
        // Commands starting by '-a..'
        //----------------------------
        if (command1=='a') {

          // Append.
          if (!std::strcmp("-append",command)) {
            gmic_substitute_args();
            float align = 0;
            char axis = 0, sep = 0;
            CImg<unsigned int> ind;
            if ((std::sscanf(argument,"%c%c",
                             &axis,&end)==1 ||
                 std::sscanf(argument,"%c,%f%c",
                             &axis,&align,&end)==2) &&
                (axis=='x' || axis=='y' || axis=='z' || axis=='c')) {
              print(images,"Append image%s along the '%c'-axis, with alignment %g.",
                    gmic_selection,
                    axis,align);
              if (selection) {
                CImgList<T> subimages;
                cimg_forY(selection,l) if (images[selection[l]])
                  subimages.insert(images[selection[l]],~0U,true);
                CImg<T> img = subimages.get_append(axis,align);
                CImg<char> name = images_names[selection[0]].get_mark();
                if (is_get_version) {
                  img.move_to(images);
                  images_names.insert(name.copymark());
                } else if (selection.height()>=2) {
                  remove_images(images,images_names,selection,1,selection.height()-1);
                  img.move_to(images[selection[0]].assign());
                  name.move_to(images_names[selection[0]]);
                }
              }
            } else if ((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c,%c%c",
                                    indices,&sep,&axis,&end)==3 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c,%c,%f%c",
                                    indices,&sep,&axis,&(align=0),&end)==4) &&
                       (axis=='x' || axis=='y' || axis=='z' || axis=='c') &&
                       sep==']' &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-append",true,
                                           false,CImg<char>::empty())).height()==1) {
              print(images,"Append image [%u] to image%s, along the '%c'-axis, with alignment %g.",
                    *ind,gmic_selection,axis,align);
              const CImg<T> img = gmic_image_arg(*ind);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],append(img,axis,align));
            } else arg_error("append");
            is_released = false; ++position; continue;
          }

          // Autocrop.
          if (!std::strcmp("-autocrop",command)) {
            gmic_substitute_args();
            CImg<T> is_arg;
            if (*argument && std::sscanf(argument,"%4095[0-9.,eE+-]%c",formula,&end)==1)
              try { CImg<T>(1).fill(argument,true).move_to(is_arg); }
              catch (CImgException&) { is_arg.assign(); }
            if (is_arg) {
              print(images,"Auto-crop image%s by vector '%s'.",
                    gmic_selection,
                    argument_text);
              ++position;
            } else print(images,"Auto-crop image%s.",
                         gmic_selection);
            cimg_forY(selection,l) {
              CImg<T>& img = images[selection[l]];
              if (is_arg) {
                const CImg<T> col = CImg<T>(img.spectrum()).fill(argument,true);
                gmic_apply(img,gmic_autocrop(col));
              }
              else gmic_apply(img,gmic_autocrop());
            }
            is_released = false; continue;
          }

#ifdef gmic_float

          // Add.
          gmic_arithmetic_item("-add",
                               operator+=,
                               "Add %g%s to image%s",
                               value,ssep,gmic_selection,T,
                               operator+=,
                               "Add image [%d] to image%s",
                               ind[0],gmic_selection,
                               "Add expression %s to image%s",
                               argument_text,gmic_selection,
                               "Add image%s");

          // Add 3d objects together, or shift a 3d object.
          if (!std::strcmp("-add3d",command)) {
            gmic_substitute_args();
            float tx = 0, ty = 0, tz = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"%f%c",
                            &tx,&end)==1 ||
                std::sscanf(argument,"%f,%f%c",
                            &tx,&ty,&end)==2 ||
                std::sscanf(argument,"%f,%f,%f%c",
                            &tx,&ty,&tz,&end)==3) {
              print(images,"Shift 3d object%s by displacement (%g,%g,%g).",
                    gmic_selection,
                    tx,ty,tz);
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (!images[ind].is_CImg3d(false,message))
                  error(images,
                        "Command 'add3d': Invalid 3d object [%d], in selected image%s (%s).",
                        ind,gmic_selection,message);
                gmic_apply(images[ind],shift_CImg3d(tx,ty,tz));
              }
              ++position;
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                       sep==']' &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-add3d",true,
                                           false,CImg<char>::empty())).height()==1) {
              const CImg<T> img0 = gmic_image_arg(*ind);
              if (!img0.is_CImg3d(true,message))
                error(images,"Command 'add3d': Invalid 3d object [%u], in specified "
                      "argument '%s' (%s).",
                      *ind,argument_text,message);
              print(images,"Merge 3d object%s with 3d object [%u].",
                    gmic_selection,*ind);
              CImgList<T> nimages(2);
              nimages[1].assign(img0,true);
              cimg_forY(selection,l) {
                const unsigned int _ind = selection[l];
                CImg<T> img = images[_ind];
                if (!img.is_CImg3d(true,message))
                  error(images,
                        "Command 'add3d': Invalid 3d object [%d], in selected image%s (%s).",
                        _ind,gmic_selection,message);
                nimages[0].assign(img,true);
                CImg<T> res = CImg<T>::append_CImg3d(nimages);
                if (is_get_version) {
                  res.move_to(images);
                  images_names[_ind].get_mark().copymark().move_to(images_names);
                } else {
                  res.move_to(images[_ind].assign());
                  images_names[_ind].mark();
                }
              }
              ++position;
            } else {
              print(images,"Merge 3d object%s.",
                    gmic_selection);
              if (selection) {
                CImgList<T> subimages(selection.height());
                cimg_forY(selection,l) subimages[l].assign(images[selection[l]],true);
                CImg<T> img = CImg<T>::append_CImg3d(subimages);
                if (!img) cimg_forY(selection,l) {
                    const unsigned int ind = selection[l];
                    if (!images[ind].is_CImg3d(true,message))
                      error(images,
                            "Command 'add3d': Invalid 3d object [%d], in selected image%s (%s).",
                            ind,gmic_selection,message);
                  }
                CImg<char> name = images_names[selection[0]].get_mark();
                if (is_get_version) {
                  img.move_to(images);
                  images_names.insert(name.copymark());
                } else if (selection.height()>=2) {
                  remove_images(images,images_names,selection,1,selection.height()-1);
                  img.move_to(images[selection[0]].assign());
                  name.move_to(images_names[selection[0]]);
                }
              }
            }
            is_released = false; continue;
          }

          // Absolute value.
          gmic_simple_item("-abs",abs,"Compute pointwise absolute value of image%s.");

          // Bitwise and.
          gmic_arithmetic_item("-and",
                               operator&=,
                               "Compute bitwise AND of image%s by %g%s",
                               gmic_selection,value,ssep,T,
                               operator&=,
                               "Compute bitwise AND of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute bitwise AND of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential bitwise AND of image%s");

          // Arc-tangent (two arguments).
          if (!std::strcmp("-atan2",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                            indices,&sep,&end)==2 && sep==']' &&
                (ind=selection2cimg(indices,images.size(),images_names,"-atan2",true,
                                    false,CImg<char>::empty())).height()==1) {
              print(images,"Compute pointwise oriented arc-tangent of image%s, "
                    "with x-argument [%u].",
                    gmic_selection,
                    *ind);
              const CImg<T> img0 = gmic_image_arg(*ind);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],atan2(img0));
            } else arg_error("atan2");
            is_released = false; ++position; continue;
          }

          // Arc-cosine.
          gmic_simple_item("-acos",acos,"Compute pointwise arc-cosine of image%s.");

          // Arc-sine.
          gmic_simple_item("-asin",asin,"Compute pointwise arc-sine of image%s.");

          // Arc-tangent.
          gmic_simple_item("-atan",atan,"Compute pointwise arc-tangent of image%s.");

          // Draw axes.
          if (!std::strcmp("-axes",command)) {
            gmic_substitute_args();
            float xmin = 0, xmax = 0, ymin = 0, ymax = 0, opacity = 1, siz = 13;
            unsigned int pattern = ~0U;
            char seph = 0;
            *color = 0;
            if (std::sscanf(argument,"%f,%f%c",
                            &xmin,&xmax,&end)==2 ||
                std::sscanf(argument,"%f,%f,%f,%f%c",
                            &xmin,&xmax,&ymin,&ymax,&end)==4 ||
                std::sscanf(argument,"%f,%f,%f,%f,%f%c",
                            &xmin,&xmax,&ymin,&ymax,&siz,&end)==5 ||
                std::sscanf(argument,"%f,%f,%f,%f,%f,%f%c",
                            &xmin,&xmax,&ymin,&ymax,&siz,&opacity,&end)==6 ||
                (std::sscanf(argument,"%f,%f,%f,%f,%f,%f,0%c%x%c",
                             &xmin,&xmax,&ymin,&ymax,&siz,&opacity,&seph,&pattern,&end)==8 &&
                 seph=='x') ||
                (std::sscanf(argument,"%f,%f,%f,%f,%f,%f,%4095[0-9.eE,+-]%c",
                             &xmin,&xmax,&ymin,&ymax,&siz,&opacity,color,&end)==7 &&
                 (pattern=~0U)) ||
                (*color=0,std::sscanf(argument,"%f,%f,%f,%f,%f,%f,0%c%x,%4095[0-9.eE,+-]%c",
                                      &xmin,&xmax,&ymin,&ymax,&siz,&opacity,
                                      &seph,&pattern,color,&end)==9 && seph=='x')) {
              siz = cimg::round(siz);
              print(images,"Draw xy-axes on image%s, with x-range (%g,%g), y-range (%g,%g), "
                    "font height %g, opacity %g, pattern 0x%x and color (%s).",
                    gmic_selection,
                    xmin,xmax,
                    ymin,ymax,
                    siz,opacity,pattern,
                    *color?color:"default");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                gmic_apply(img,draw_axes(xmin,xmax,ymin,ymax,col.data(),opacity,
                                         -60,-60,0,0,pattern,pattern,(unsigned int)siz));
              }
            } else arg_error("axes");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='a'.

        //----------------------------
        // Commands starting by '-b..'
        //----------------------------
        else if (command1=='b') {

#ifdef gmic_float

          // Blur.
          if (!std::strcmp("-blur",command)) {
            gmic_substitute_args();
            unsigned int boundary = 1, is_gaussian = 0;
            float sigma = -1;
            char sep = 0;
            if ((std::sscanf(argument,"%f%c",
                             &sigma,&end)==1 ||
                 (std::sscanf(argument,"%f%c%c",
                              &sigma,&sep,&end)==2 && sep=='%') ||
                 std::sscanf(argument,"%f,%u%c",
                             &sigma,&boundary,&end)==2 ||
                 (std::sscanf(argument,"%f%c,%u%c",
                              &sigma,&sep,&boundary,&end)==3 && sep=='%') ||
                 std::sscanf(argument,"%f,%u,%u%c",
                             &sigma,&boundary,&is_gaussian,&end)==3 ||
                 (std::sscanf(argument,"%f%c,%u,%u%c",
                              &sigma,&sep,&boundary,&is_gaussian,&end)==4 && sep=='%')) &&
                sigma>=0 && boundary<=1 && is_gaussian<=1) {
              print(images,"Blur image%s, with standard deviation %g%s, %s boundary and %s kernel.",
                    gmic_selection,
                    sigma,sep=='%'?"%":"",
                    boundary?"neumann":"dirichlet",
                    is_gaussian?"gaussian":"quasi-gaussian");
              if (sep=='%') sigma = -sigma;
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],blur(sigma,(bool)boundary,(bool)is_gaussian));
            } else arg_error("blur");
            is_released = false; ++position; continue;
          }

          // Bitwise right shift.
          gmic_arithmetic_item("-bsr",
                               operator>>=,
                               "Compute bitwise right shift of image%s by %g%s",
                               gmic_selection,value,ssep,T,
                               operator>>=,
                               "Compute bitwise right shift of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute bitwise right shift of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential bitwise right shift of image%s");

          // Bitwise left shift.
          gmic_arithmetic_item("-bsl",
                               operator<<=,
                               "Compute bitwise left shift of image%s by %g%s",
                               gmic_selection,value,ssep,T,
                               operator<<=,
                               "Compute bitwise left shift of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute bitwise left shift of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential bitwise left shift of image%s");

          // Bilateral filter.
          if (!std::strcmp("-bilateral",command)) {
            gmic_substitute_args();
            float sigma_s = 0, sigma_r = 0;
            char sep =  0;
            if ((std::sscanf(argument,"%f,%f%c",
                             &sigma_s,&sigma_r,&end)==2 ||
                 (std::sscanf(argument,"%f%c,%f%c",
                              &sigma_s,&sep,&sigma_r,&end)==3 && sep=='%')) &&
                sigma_s>=0 && sigma_r>=0) {
              print(images,"Apply bilateral filter on image%s, with standard deviations %g%s "
                    "and %g.",
                    gmic_selection,
                    sigma_s,sep=='%'?"%":"",
                    sigma_r);
              if (sep=='%') sigma_s = -sigma_s;
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],blur_bilateral(sigma_s,sigma_r));
            } else arg_error("bilateral");
            is_released = false; ++position; continue;
          }

          // Set 3d background color.
          if (!std::strcmp("-background3d",item)) {
            gmic_substitute_args();
            float R = 0, G = 0, B = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            const int nb = std::sscanf(argument,"%f,%f,%f%c",
                                       &R,&G,&B,&end);
            R = cimg::round(R);
            G = cimg::round(G);
            B = cimg::round(B);
            if (nb>=1 && nb<=3) {
              switch (nb) {
              case 1 : background3d.assign(1,1,1,3,(unsigned char)R); break;
              case 2 : background3d.assign(1,1,1,3,(unsigned char)R,(unsigned char)G,0); break;
              case 3 : background3d.assign(1,1,1,3,(unsigned char)R,(unsigned char)G,
                                           (unsigned char)B); break;
              }
              print(images,"Set 3d background color to (%u,%u,%u).",
                    (unsigned int)R,(unsigned int)G,(unsigned int)B);
              ++position;
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                       sep==']' &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-background3d",true,
                                           false,CImg<char>::empty())).height()==1) {
              print(images,"Set 3d background from image [%u].",*ind);
              background3d = images[*ind];
              ++position;
            } else {
              print(images,"Reset 3d background to default.");
              background3d.assign(1,2,1,3).fill(32,64,32,116,64,96).resize(1,256,1,3,3);
            }
            continue;
          }

#endif // #ifdef gmic_float
        } // command1=='b'.

        //----------------------------
        // Commands starting by '-c..'
        //----------------------------
        else if (command1=='c') {

          // Check expression or filename.
          if (!std::strcmp("-check",item)) {
            gmic_substitute_args();
            CImg<char> arg_check(argument,std::strlen(argument)+1);
            gmic_strreplace(arg_check);
            bool is_cond = false, is_filename = false;
            const CImg<T> &img = images.size()?images.back():CImg<T>::empty();
            try { if (img.eval(arg_check)) is_cond = true; }
            catch (CImgException&) {
              is_filename = true; is_cond = false;
              try {
                std::FILE *file = cimg::fopen(arg_check,"r");
                if (file) { is_cond = true; cimg::fclose(file); }
              } catch (CImgException&) {}
            }
            if (verbosity>0 || is_debug) {
              print(images,"Check %s '%s' -> %s.",
                    is_filename?"filename":"expression",
                    argument_text,
                    is_filename?(is_cond?"found":"not found"):(is_cond?"true":"false"));
            }
            if (!is_cond) {
              if (scope.size()>1 && scope.back()[0]!='*')
                error(scope.back().data(),images,"Command 'check': %s '%s' %s.",
                      is_filename?"filename":"expression",
                      argument_text,
                      is_filename?"does not exist":"is false");
              else error(images,"Command 'check': %s '%s' %s.",
                         is_filename?"filename":"expression",
                         argument_text,
                         is_filename?"does not exist":"is false");
            }
            ++position; continue;
          }

          // Crop.
          if (!std::strcmp("-crop",command)) {
            gmic_substitute_args();
            static char st0[256], st1[256], st2[256], st3[256], st4[256],
              st5[256], st6[256], st7[256];
            char sep0 = 0, sep1 = 0, sep2 = 0, sep3 = 0, sep4 = 0, sep5 = 0, sep6 = 0, sep7 = 0;
            float a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0;
            *st0 = *st1 = *st2 = *st3 = *st4 = *st5 = *st6 = *st7 = 0;
            unsigned int boundary = 0;
            if ((boundary=0,std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                                        st0,st1,&end)==2 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%u%c",
                             st0,st1,&boundary,&end)==3) &&
                (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                 (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                 (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%')) &&
                boundary<=1) {
              print(images,"Crop image%s with selection (%g%s) x (%g%s) and %s boundary.",
                    gmic_selection,
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    boundary?"neumann":"dirichlet");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  x0 = (int)cimg::round(sep0=='%'?a0*(img.width()-1)/100:a0),
                  x1 = (int)cimg::round(sep1=='%'?a1*(img.width()-1)/100:a1);
                gmic_apply(img,crop(x0,x1,(bool)boundary));
              }
              ++position;
            } else if ((boundary=0,std::sscanf(argument,
                                               "%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                               "%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                                               st0,st1,st2,st3,&end)==4 ||
                        std::sscanf(argument,
                                    "%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                    "%255[0-9.eE%+-],%255[0-9.eE%+-],%u%c",
                                    st0,st1,st2,st3,&boundary,&end)==5) &&
                       (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                        (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                       (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                        (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%')) &&
                       (std::sscanf(st2,"%f%c",&a2,&end)==1 ||
                        (std::sscanf(st2,"%f%c%c",&a2,&sep2,&end)==2 && sep2=='%')) &&
                       (std::sscanf(st3,"%f%c",&a3,&end)==1 ||
                        (std::sscanf(st3,"%f%c%c",&a3,&sep3,&end)==2 && sep3=='%')) &&
                       boundary<=1) {
              print(images,
                    "Crop image%s with selection (%g%s,%g%s) x (%g%s,%g%s) and %s boundary.",
                    gmic_selection,
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    a2,sep2=='%'?"%":"",
                    a3,sep3=='%'?"%":"",
                    boundary?"neumann":"dirichlet");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  x0 = (int)cimg::round(sep0=='%'?a0*(img.width()-1)/100:a0),
                  y0 = (int)cimg::round(sep1=='%'?a1*(img.height()-1)/100:a1),
                  x1 = (int)cimg::round(sep2=='%'?a2*(img.width()-1)/100:a2),
                  y1 = (int)cimg::round(sep3=='%'?a3*(img.height()-1)/100:a3);
                gmic_apply(img,crop(x0,y0,x1,y1,(bool)boundary));
              }
              ++position;
            } else if ((boundary=0,std::sscanf(argument,
                                               "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                               "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                                               st0,st1,st2,st3,st4,st5,&end)==6 ||
                        std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                    "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%u%c",
                                    st0,st1,st2,st3,st4,st5,&boundary,&end)==7) &&
                       (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                        (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                       (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                        (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%')) &&
                       (std::sscanf(st2,"%f%c",&a2,&end)==1 ||
                        (std::sscanf(st2,"%f%c%c",&a2,&sep2,&end)==2 && sep2=='%')) &&
                       (std::sscanf(st3,"%f%c",&a3,&end)==1 ||
                        (std::sscanf(st3,"%f%c%c",&a3,&sep3,&end)==2 && sep3=='%')) &&
                       (std::sscanf(st4,"%f%c",&a4,&end)==1 ||
                        (std::sscanf(st4,"%f%c%c",&a4,&sep4,&end)==2 && sep4=='%')) &&
                       (std::sscanf(st5,"%f%c",&a5,&end)==1 ||
                        (std::sscanf(st5,"%f%c%c",&a5,&sep5,&end)==2 && sep5=='%')) &&
                       boundary<=1) {
              print(images,"Crop image%s with selection (%g%s,%g%s,%g%s) x (%g%s,%g%s,%g%s) "
                    "and %s boundary.",
                    gmic_selection,
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    a2,sep2=='%'?"%":"",
                    a3,sep3=='%'?"%":"",
                    a4,sep4=='%'?"%":"",
                    a5,sep5=='%'?"%":"",
                    boundary?"neumann":"dirichlet");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  x0 = (int)cimg::round(sep0=='%'?a0*(img.width()-1)/100:a0),
                  y0 = (int)cimg::round(sep1=='%'?a1*(img.height()-1)/100:a1),
                  z0 = (int)cimg::round(sep2=='%'?a2*(img.depth()-1)/100:a2),
                  x1 = (int)cimg::round(sep3=='%'?a3*(img.width()-1)/100:a3),
                  y1 = (int)cimg::round(sep4=='%'?a4*(img.height()-1)/100:a4),
                  z1 = (int)cimg::round(sep5=='%'?a5*(img.depth()-1)/100:a5);
                gmic_apply(img,crop(x0,y0,z0,x1,y1,z1,(bool)boundary));
              }
              ++position;
            } else if ((boundary=0,std::sscanf(argument,
                                               "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                               "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                               "%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                                               st0,st1,st2,st3,st4,st5,st6,st7,&end)==8 ||
                        std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                    "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                    "%255[0-9.eE%+-],%255[0-9.eE%+-],%u%c",
                                    st0,st1,st2,st3,st4,st5,st6,st7,&boundary,&end)==9) &&
                       (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                        (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                       (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                        (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%')) &&
                       (std::sscanf(st2,"%f%c",&a2,&end)==1 ||
                        (std::sscanf(st2,"%f%c%c",&a2,&sep2,&end)==2 && sep2=='%')) &&
                       (std::sscanf(st3,"%f%c",&a3,&end)==1 ||
                        (std::sscanf(st3,"%f%c%c",&a3,&sep3,&end)==2 && sep3=='%')) &&
                       (std::sscanf(st4,"%f%c",&a4,&end)==1 ||
                        (std::sscanf(st4,"%f%c%c",&a4,&sep4,&end)==2 && sep4=='%')) &&
                       (std::sscanf(st5,"%f%c",&a5,&end)==1 ||
                        (std::sscanf(st5,"%f%c%c",&a5,&sep5,&end)==2 && sep5=='%')) &&
                       (std::sscanf(st6,"%f%c",&a6,&end)==1 ||
                        (std::sscanf(st6,"%f%c%c",&a6,&sep6,&end)==2 && sep6=='%')) &&
                       (std::sscanf(st7,"%f%c",&a7,&end)==1 ||
                        (std::sscanf(st7,"%f%c%c",&a7,&sep7,&end)==2 && sep7=='%')) &&
                       boundary<=1) {
              print(images,
                    "Crop image%s with selection (%g%s,%g%s,%g%s,%g%s) x (%g%s,%g%s,%g%s,%g%s) "
                    "and %s boundary.",
                    gmic_selection,
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    a2,sep2=='%'?"%":"",
                    a3,sep3=='%'?"%":"",
                    a4,sep4=='%'?"%":"",
                    a5,sep5=='%'?"%":"",
                    a6,sep6=='%'?"%":"",
                    a7,sep7=='%'?"%":"",
                    boundary?"neumann":"dirichlet");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  x0 = (int)cimg::round(sep0=='%'?a0*(img.width()-1)/100:a0),
                  y0 = (int)cimg::round(sep1=='%'?a1*(img.height()-1)/100:a1),
                  z0 = (int)cimg::round(sep2=='%'?a2*(img.depth()-1)/100:a2),
                  v0 = (int)cimg::round(sep3=='%'?a3*(img.spectrum()-1)/100:a3),
                  x1 = (int)cimg::round(sep4=='%'?a4*(img.width()-1)/100:a4),
                  y1 = (int)cimg::round(sep5=='%'?a5*(img.height()-1)/100:a5),
                  z1 = (int)cimg::round(sep6=='%'?a6*(img.depth()-1)/100:a6),
                  v1 = (int)cimg::round(sep7=='%'?a7*(img.spectrum()-1)/100:a7);
                gmic_apply(img,crop(x0,y0,z0,v0,x1,y1,z1,v1,(bool)boundary));
              }
              ++position;
            } else {
#if cimg_display==0
              print(images,"Crop image%s in interactive mode (skipped, no display support).",
                    gmic_selection);
#else // #if cimg_display==0
              bool is_available_display = false;
              try {
                is_available_display = (bool)CImgDisplay::screen_width();
              } catch (CImgDisplayException&) {
                print(images,"Crop image%s in interactive mode (skipped, no display available).",
                      gmic_selection);
              }
              if (is_available_display) {
                print(images,"Crop image%s in interactive mode.",
                      gmic_selection);
                CImgDisplay _disp, &disp = instant_window[0]?instant_window[0]:_disp;
                cimg_forY(selection,l) {
                  CImg<T>& img = images[selection[l]];
                  if (disp) disp.resize(cimg_fitscreen(img.width(),img.height(),1),false);
                  else disp.assign(cimg_fitscreen(img.width(),img.height(),1),0,1);
                  disp.set_title("%s: crop",gmic_basename(images_names[selection[l]].data()));
                  const CImg<int> s = img.get_select(disp,2);
                  print(images,"Crop image [%d] with selection (%d,%d,%d) x (%d,%d,%d).",
                        selection[l],
                        s[0],s[1],s[2],
                        s[3],s[4],s[5]);
                  gmic_apply(img,crop(s[0],s[1],s[2],s[3],s[4],s[5]));
                }
              }
#endif // #if cimg_display==0
            }
            is_released = false; continue;
          }

          // Keep channels.
          if (!std::strcmp("-channels",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind0, ind1;
            float value0 = 0, value1 = 0;
            char sep0 = 0, sep1 = 0;
            *argx = *argy = 0;
            if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-]%c",
                            argx,&end)==1 &&
                ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c]",indices,&sep0,&end)==2 &&
                  sep0==']' &&
                  (ind0=selection2cimg(indices,images.size(),images_names,"-channels",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%'))) {
              if (ind0) { value0 = images[*ind0].spectrum() - 1.0f; sep0 = 0; }
              print(images,"Keep channel %g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.spectrum()-1)/100:value0);
                gmic_apply(img,channel(nvalue0));
              }
            } else if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                                   argx,argy,&end)==2 &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind0=selection2cimg(indices,images.size(),images_names,"-channels",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                        (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%')) &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",formula,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind1=selection2cimg(formula,images.size(),images_names,"-channels",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argy,"%f%c",&value1,&end)==1 ||
                        (std::sscanf(argy,"%f%c%c",&value1,&sep1,&end)==2 && sep1=='%'))) {
              if (ind0) { value0 = images[*ind0].spectrum() - 1.0f; sep0 = 0; }
              if (ind1) { value1 = images[*ind1].spectrum() - 1.0f; sep1 = 0; }
              print(images,"Keep channels %g%s..%g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.spectrum()-1)/100:value0),
                  nvalue1 = (int)cimg::round(sep1=='%'?value1*(img.spectrum()-1)/100:value1);
                gmic_apply(img,channels(nvalue0,nvalue1));
              }
            } else arg_error("channels");
            is_released = false; ++position; continue;
          }

          // Keep columns.
          if (!std::strcmp("-columns",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind0, ind1;
            float value0 = 0, value1 = 0;
            char sep0 = 0, sep1 = 0;
            *argx = *argy = 0;
            if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-]%c",
                            argx,&end)==1 &&
                ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c]",indices,&sep0,&end)==2 &&
                  sep0==']' &&
                  (ind0=selection2cimg(indices,images.size(),images_names,"-columns",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%'))) {
              if (ind0) { value0 = images[*ind0].width() - 1.0f; sep0 = 0; }
              print(images,"Keep column %g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.width()-1)/100:value0);
                gmic_apply(img,column(nvalue0));
              }
            } else if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                                   argx,argy,&end)==2 &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind0=selection2cimg(indices,images.size(),images_names,"-columns",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                        (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%')) &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",formula,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind1=selection2cimg(formula,images.size(),images_names,"-columns",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argy,"%f%c",&value1,&end)==1 ||
                        (std::sscanf(argy,"%f%c%c",&value1,&sep1,&end)==2 && sep1=='%'))) {
              if (ind0) { value0 = images[*ind0].width() - 1.0f; sep0 = 0; }
              if (ind1) { value1 = images[*ind1].width() - 1.0f; sep1 = 0; }
              print(images,"Keep columns %g%s..%g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.width()-1)/100:value0),
                  nvalue1 = (int)cimg::round(sep1=='%'?value1*(img.width()-1)/100:value1);
                gmic_apply(img,columns(nvalue0,nvalue1));
              }
            } else arg_error("columns");
            is_released = false; ++position; continue;
          }

          // Import custom commands.
          if (!std::strcmp("-command",item)) {
            gmic_substitute_args();
            CImg<char> arg_command(argument,std::strlen(argument)+1);
            gmic_strreplace(arg_command);
            std::FILE *file = std::fopen(arg_command,"rb");
            unsigned int siz = 0;
            for (unsigned int l = 0; l<256; ++l) siz+=commands[l].size();
            if (file) {
              print(images,"Import custom commands from file '%s'",
                    argument_text);
              add_commands(file,commands_names,commands,commands_has_arguments);
              std::fclose(file);
            } else if (!cimg::strncasecmp(arg_command,"http://",7) ||
                       !cimg::strncasecmp(arg_command,"https://",8)) { // Try to read from network.
              print(images,"Import custom commands from URL '%s'",
                    argument_text);
              char filename_tmp[512] = { 0 };
              try {
                file = std::fopen(cimg::load_network_external(arg_command,filename_tmp),"r");
              } catch (...) {
                file = 0;
              }
              if (file) {
                add_commands(file,commands_names,commands,commands_has_arguments);
                std::fclose(file);
              } else
                error(images,"Command '-command': Unable to reach custom commands file '%s' "
                      "from network.",
                      argument_text);
              std::remove(filename_tmp);
            } else {
              print(images,"Import custom commands from expression '%s'",
                    argument_text);
              add_commands(arg_command,commands_names,commands,commands_has_arguments);
            }
            if (verbosity>=0 || is_debug) {
              unsigned int nb_added = 0;
              for (unsigned int l = 0; l<256; ++l) nb_added+=commands[l].size();
              nb_added-=siz;
              std::fprintf(cimg::output()," (added %u command%s, total %u).",
                           nb_added,nb_added>1?"s":"",siz+nb_added);
              std::fflush(cimg::output());
            }
            ++position; continue;
          }

          // Camera input.
          if (!std::strcmp("-camera",item)) {
            gmic_substitute_args();
            float cam_index = -1, nb_frames = 1, skip_frames = 0;
            unsigned int release_cam = 0;
            if ((std::sscanf(argument,"%f%c",
                             &cam_index,&end)==1 ||
                 std::sscanf(argument,"%f,%f%c",
                             &cam_index,&nb_frames,&end)==2 ||
                 std::sscanf(argument,"%f,%f,%f%c",
                             &cam_index,&nb_frames,&skip_frames,&end)==3 ||
                 std::sscanf(argument,"%f,%f,%f,%u%c",
                             &cam_index,&nb_frames,&skip_frames,&release_cam,&end)==4) &&
                cam_index>=-1 && nb_frames>=0 && skip_frames>=0 && release_cam<=1) ++position;
            cam_index = cimg::round(cam_index);
            nb_frames = cimg::round(nb_frames);
            skip_frames = cimg::round(skip_frames);
            if (release_cam) {
              if (cam_index<0) print(images,"Release default camera.");
              else print(images,"Release camera #%g.",cam_index);
              CImg<T>::get_load_camera((int)cam_index,true);
            } else {
              if (cam_index<0) {
                print(images,"Insert %g image%s from default camera, with %g frames skipping.",
                      nb_frames,nb_frames>1?"s":"",skip_frames);
                cimg_snprintf(title,sizeof(title),"[Default camera]");
              } else {
                print(images,"Insert %g image%s from camera #%g, with %g frames skipping.",
                      cam_index,nb_frames,nb_frames>1?"s":"",skip_frames);
                cimg_snprintf(title,sizeof(title),"[Camera #%g]",cam_index);
              }
              const CImg<char> _title = CImg<char>::string(title);
              if (nb_frames>1) {
                std::fputc('\n',cimg::output());
                std::fflush(cimg::output());
              }
              for (unsigned int k = 0; k<(unsigned int)nb_frames; ++k) {
                if (nb_frames>1 && (verbosity>=0 || is_debug)) {
                  std::fprintf(cimg::output(),"\r  > Image %u/%u        ",
                               k+1,(unsigned int)nb_frames);
                  std::fflush(cimg::output());
                }
                CImg<T>::get_load_camera((int)cam_index,(unsigned int)skip_frames,false).
                  move_to(images);
                images_names.insert(_title);
              }
            }
            is_released = false; continue;
          }

#ifdef gmic_float

          // Cut.
          if (!std::strcmp("-cut",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind0, ind1;
            double value0 = 0, value1 = 0;
            char sep0 = 0, sep1 = 0;
            *argx = *argy = 0;
            if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                            argx,argy,&end)==2 &&
                ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                  sep0==']' &&
                  (ind0=selection2cimg(indices,images.size(),images_names,"-cut",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 (std::sscanf(argx,"%lf%c%c",&value0,&sep0,&end)==2 && sep0=='%') ||
                 std::sscanf(argx,"%lf%c",&value0,&end)==1) &&
                ((std::sscanf(argy,"[%255[a-zA-Z0-9_.%+-]%c%c",formula,&sep1,&end)==2 &&
                  sep1==']' &&
                  (ind1=selection2cimg(formula,images.size(),images_names,"-cut",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 (std::sscanf(argy,"%lf%c%c",&value1,&sep1,&end)==2 && sep1=='%') ||
                 std::sscanf(argy,"%lf%c",&value1,&end)==1)) {
              if (ind0) { value0 = images[*ind0].min(); sep0 = 0; }
              if (ind1) { value1 = images[*ind1].max(); sep1 = 0; }
              print(images,"Cut image%s in range [%g%s,%g%s].",
                    gmic_selection,
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                double vmin = 0, vmax = 0, nvalue0 = value0, nvalue1 = value1;
                if (sep0=='%' || sep1=='%') {
                  if (img) vmax = (double)img.max_min(vmin);
                  if (sep0=='%') nvalue0 = vmin + (vmax-vmin)*value0/100;
                  if (sep1=='%') nvalue1 = vmin + (vmax-vmin)*value1/100;
                }
                gmic_apply(img,cut((T)nvalue0,(T)nvalue1));
              }
              ++position;
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                       sep0==']' &&
                       (ind0=selection2cimg(indices,images.size(),images_names,"-cut",true,
                                            false,CImg<char>::empty())).height()==1) {
              if (images[*ind0]) value1 = (double)images[*ind0].max_min(value0);
              print(images,"Cut image%s in range [%g,%g].",
                    gmic_selection,
                    value0,
                    value1);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],cut((T)value0,(T)value1));
              ++position;
            } else {
#if cimg_display==0
              print(images,"Cut image%s in interactive mode (skipped, no display support).",
                    gmic_selection);
#else // #if cimg_display==0
              bool is_available_display = false;
              try {
                is_available_display = (bool)CImgDisplay::screen_width();
              } catch (CImgDisplayException&) {
                print(images,"Cut image%s in interactive mode (skipped, no display available).",
                      gmic_selection);
              }
              if (is_available_display) {
                print(images,"Cut image%s in interactive mode.",
                      gmic_selection);
                CImgDisplay _disp, &disp = instant_window[0]?instant_window[0]:_disp;
                cimg_forY(selection,l) {
                  CImg<T> &img = images[selection[l]];
                  if (img) {
                    CImg<T> visu = img.depth()>1?img.get_projections2d(img.width()/2,
                                                                       img.height()/2,
                                                                       img.depth()/2).
                      channels(0,cimg::min(3,img.spectrum())-1):
                      img.get_channels(0,cimg::min(3,img.spectrum()-1));
                    const unsigned int
                      w = CImgDisplay::_fitscreen(visu.width(),visu.height(),1,256,-85,false),
                      h = CImgDisplay::_fitscreen(visu.width(),visu.height(),1,256,-85,true);
                    if (disp) disp.resize(w,h,false); else disp.assign(w,h,0,0);
                    double vmin = 0, vmax = (double)img.max_min(vmin),
                      percent0 = 0, percent1 = 100;
                    bool stopflag = false, is_clicked = false;
                    int omx = -1, omy = -1;
                    CImg<unsigned char> res;
                    for (disp.show().flush(); !stopflag; ) {
                      const unsigned char white[] = { 255,255,255 }, black[] = { 0,0,0 };
                      const unsigned int key = disp.key();
                      if (!res)
                        disp.display((res=visu.get_cut((T)(vmin + percent0*(vmax-vmin)/100),
                                                       (T)(vmin + percent1*(vmax-vmin)/100)).
                                      resize(disp).normalize(0,255)).
                                     draw_text(0,0,"Cut [%g,%g] = [%.3g%%,%.3g%%]",
                                               white,black,0.7f,13,
                                               (double)(vmin + percent0*(vmax-vmin)/100),
                                               (double)(vmin + percent1*(vmax-vmin)/100),
                                               percent0,percent1)).
                          set_title("%s (%dx%dx%dx%d)",
                                    gmic_basename(images_names[selection[l]].data()),
                                    img.width(),img.height(),img.depth(),img.spectrum()).wait();
                      const int mx = disp.mouse_x(), my = disp.mouse_y();
                      if (disp.button()) {
                        if (mx>=0 && my>=0 && (mx!=omx || my!=omy)) {
                          percent0 = (my-16)*100.0/(disp.height()-32);
                          percent1 = (mx-16)*100.0/(disp.width()-32);
                          if (percent0<0) percent0 = 0; else if (percent0>101) percent0 = 101;
                          if (percent1<0) percent1 = 0; else if (percent1>101) percent1 = 101;
                          if (percent0>percent1) cimg::swap(percent0,percent1);
                          omx = mx; omy = my; res.assign();
                        }
                        is_clicked = true;
                      } else if (is_clicked) break;
                      if (disp.is_closed() || (key && key!=cimg::keyCTRLLEFT)) stopflag = true;
                      if (key==cimg::keyD && disp.is_keyCTRLLEFT()) {
                        disp.resize(cimg_fitscreen(3*disp.width()/2,3*disp.height()/2,1),
                                    stopflag=false).set_key(cimg::keyD,false);
                        res.assign();
                      }
                      if (key==cimg::keyC && disp.is_keyCTRLLEFT()) {
                        disp.resize(cimg_fitscreen(2*disp.width()/3,2*disp.height()/3,1),
                                    stopflag=false).set_key(cimg::keyC,false);
                        res.assign();
                      }
                      if (disp.is_resized()) { disp.resize(false); res.assign(); }
                    }
                    print(images,"Cut image [%d] in range [%g,%g] = [%.3g%%,%.3g%%].",
                          selection[l],
                          (double)(vmin + percent0*(vmax-vmin)/100),
                          (double)(vmin + percent1*(vmax-vmin)/100),
                          percent0,percent1);
                    gmic_apply(img,cut((T)(vmin + percent0*(vmax-vmin)/100),
                                       (T)(vmin + percent1*(vmax-vmin)/100)));
                  } else { gmic_apply(img,replace(img)); }
                }
              }
#endif // #if cimg_display==0
            }
            is_released = false; continue;
          }

          // Cosine.
          gmic_simple_item("-cos",cos,"Compute pointwise cosine of image%s.");

          // Convolve.
          if (!std::strcmp("-convolve",command)) {
            gmic_substitute_args();
            unsigned int boundary = 1, is_normalized = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u%c",
                             indices,&boundary,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u%c",
                             indices,&boundary,&is_normalized,&end)==3) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-convolve",true,
                                    false,CImg<char>::empty())).height()==1 &&
                boundary<=1) {
              print(images,
                    "Convolve image%s with mask [%u] and %s boundary, with%s normalization.",
                    gmic_selection,
                    *ind,
                    boundary?"neumann":"dirichlet",
                    is_normalized?"":"out");
              const CImg<T> mask = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],convolve(mask,boundary,(bool)is_normalized));
            } else arg_error("convolve");
            is_released = false; ++position; continue;
          }

          // Correlate.
          if (!std::strcmp("-correlate",command)) {
            gmic_substitute_args();
            unsigned int boundary = 1, is_normalized = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u%c",
                             indices,&boundary,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u%c",
                             indices,&boundary,&is_normalized,&end)==3) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-correlate",true,
                                    false,CImg<char>::empty())).height()==1 &&
                boundary<=1) {
              print(images,
                    "Correlate image%s with mask [%u] and %s boundary, with%s normalization.",
                    gmic_selection,
                    *ind,
                    boundary?"neumann":"dirichlet",
                    is_normalized?"":"out");
              const CImg<T> mask = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],correlate(mask,boundary,(bool)is_normalized));
            } else arg_error("correlate");
            is_released = false; ++position; continue;
          }

          // Set 3d object color.
          if (!std::strcmp("-color3d",command) || !std::strcmp("-col3d",command)) {
            gmic_substitute_args();
            float R = 200, G = 200, B = 200, opacity = -1;
            if ((std::sscanf(argument,"%f%c",
                             &R,&end)==1 && ((B=G=R),1)) ||
                (std::sscanf(argument,"%f,%f%c",
                             &R,&G,&end)==2 && ((B=0),1)) ||
                std::sscanf(argument,"%f,%f,%f%c",
                            &R,&G,&B,&end)==3 ||
                std::sscanf(argument,"%f,%f,%f,%f%c",
                            &R,&G,&B,&opacity,&end)==4) {
              const bool set_opacity = (opacity>=0);
              if (set_opacity)
                print(images,"Set colors of 3d object%s to (%g,%g,%g), with opacity %g.",
                      gmic_selection,
                      R,G,B,
                      opacity);
              else
                print(images,"Set color of 3d object%s to (%g,%g,%g).",
                      gmic_selection,
                      R,G,B);
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (!images[ind].is_CImg3d(true,message))
                  error(images,"Command 'color3d': Invalid 3d object [%d], "
                        "in selected image%s (%s).",
                        ind,gmic_selection,message);
                gmic_apply(images[ind],color_CImg3d(R,G,B,opacity,true,set_opacity));
              }
            } else arg_error("color3d");
            is_released = false; ++position; continue;
          }

          // Hyperbolic cosine.
          gmic_simple_item("-cosh",cosh,"Compute pointwise hyperbolic cosine of image%s.");

#endif // #ifdef gmic_float
        } // command1=='c'.

        //----------------------------
        // Commands starting by '-d..'
        //----------------------------
        else if (command1=='d') {

          // Done.
          if (!std::strcmp("-done",item)) {
            const CImg<char> &s = scope.back();
            if (s[0]!='*' || s[1]!='r')
              error(images,"Command 'done': Not associated to a 'repeat' command "
                    "within the same scope.");
            if (--repeatdones.back()(1)) {
              ++repeatdones.back()(2);
              position = repeatdones.back()(0);
            } else {
              if (verbosity>0 || is_debug) print(images,"End 'repeat..done' block.");
              repeatdones.remove();
              scope.remove();
            }
            continue;
          }

          // Do..while.
          if (!std::strcmp("-do",item)) {
            CImg<char>::string("*do").move_to(scope);
            if (verbosity>0 || is_debug) print(images,"Start 'do..while' block.");
            CImg<unsigned int>::vector(position).move_to(dowhiles);
            continue;
          }

          // Enable debug mode (useful when '-debug' is invoked from a custom command).
          if (!std::strcmp("-debug",item)) {
            is_debug = true;
            continue;
          }

#ifdef gmic_float

          // Divide.
          gmic_arithmetic_item("-div",
                               operator/=,
                               "Divide image%s by %g%s",
                               gmic_selection,value,ssep,double,
                               div,
                               "Divide image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Divide image%s by expression %s",
                               gmic_selection,argument_text,
                               "Divide image%s");

          // Distance function.
          if (!std::strcmp("-distance",command)) {
            gmic_substitute_args();
            char sepx = 0, sepy = 0, sepz = 0, sep1 = 0, sep2 = 0;
            float x = 0, y = 0, z = 0;
            CImg<unsigned int> ind;
            double value = 0;
            int metric = 2;
            if ((std::sscanf(argument,"%lf%c",
                             &value,&end)==1 ||
                 (std::sscanf(argument,"%lf%c%c",
                              &value,&sep1,&end)==2 && sep1=='%') ||
                 std::sscanf(argument,"%lf,%d%c",
                             &value,&metric,&end)==2 ||
                 (std::sscanf(argument,"%lf%c,%d%c",
                              &value,&sep1,&metric,&end)==3 && sep1=='%')) &&
                metric>=0 && metric<=3) {
              print(images,"Compute distance map to isovalue %g%s in image%s, with %s metric.",
                    value,sep1=='%'?"%":"",
                    gmic_selection,
                    metric==0?"chebyshev":metric==1?"manhattan":metric==2?"euclidean":
                    "squared-euclidean");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                double nvalue = value;
                if (sep1=='%' && img) {
                  double vmin, vmax = (double)img.max_min(vmin);
                  nvalue = vmin + value*(vmax-vmin)/100;
                }
                gmic_apply(img,distance((T)nvalue,metric));
              }
            } else if ((std::sscanf(argument,"%lf,[%255[a-zA-Z0-9_.%+-]%c%c",
                                    &value,indices,&sep2,&end)==3 ||
                        (std::sscanf(argument,"%lf%c,[%255[a-zA-Z0-9_.%+-]%c%c",
                                     &value,&sep1,indices,&sep2,&end)==4 && sep1=='%')) &&
                       sep2==']' &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-distance",true,
                                           false,CImg<char>::empty())).height()==1) {
              print(images,"Compute distance map to isovalue %g%s in image%s, with metric [%u].",
                    value,sep1=='%'?"%":"",
                    gmic_selection,*ind);
              const CImg<T> custom_metric = gmic_image_arg(*ind);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                double nvalue = value;
                if (sep1=='%' && img) {
                  double vmin, vmax = (double)img.max_min(vmin);
                  nvalue = vmin + value*(vmax-vmin)/100;
                }
                gmic_apply(img,distance((T)nvalue,custom_metric));
              }
            } else if (std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                                   argx,argy,argz,&end)==3 &&
                       (std::sscanf(argx,"%f%c",&x,&end)==1 ||
                        (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                       (std::sscanf(argy,"%f%c",&y,&end)==1 ||
                        (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                       (std::sscanf(argz,"%f%c",&z,&end)==1 ||
                        (std::sscanf(argz,"%f%c%c",&z,&sepz,&end)==2 && sepz=='%')) &&
                       x>=0 && y>=0 && z>=0) {
              print(images,"Compute distance map to point (%g%s,%g%s,%g%s) for potential map%s.",
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    z,sepz=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y),
                  nz = (int)cimg::round(sepz=='%'?z*(img.depth()-1)/100:z);
                gmic_apply(img,distance_dijkstra(nx,ny,nz));
              }
            } else arg_error("distance");
            is_released = false; ++position; continue;
          }

          // Dilate.
          if (!std::strcmp("-dilate",command)) {
            gmic_substitute_args();
            float sx = 3, sy = 3, sz = 1;
            unsigned int boundary = 1, is_normalized = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u%c",
                             indices,&boundary,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u%c",
                             indices,&boundary,&is_normalized,&end)==3) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-dilate",true,
                                    false,CImg<char>::empty())).height()==1 &&
                boundary<=1) {
              print(images,"Dilate image%s with mask [%u] and %s boundary, with%s normalization.",
                    gmic_selection,
                    *ind,
                    boundary?"neumann":"dirichlet",
                    is_normalized?"":"out");
              const CImg<T> mask = gmic_image_arg(*ind);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],dilate(mask,boundary,
                                                                            (bool)is_normalized));
            } else if ((std::sscanf(argument,"%f%c",
                                    &sx,&end)==1) &&
                       sx>=0) {
              sx = cimg::round(sx);
              print(images,"Dilate image%s with mask of size %g and neumann boundary.",
                    gmic_selection,
                    sx);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],dilate((unsigned int)sx));
            } else if ((std::sscanf(argument,"%f,%f%c",
                                    &sx,&sy,&end)==2 ||
                        std::sscanf(argument,"%f,%f,%f%c",
                                    &sx,&sy,&sz,&end)==3) &&
                       sx>=0 && sy>=0 && sz>=0) {
              sx = cimg::round(sx);
              sy = cimg::round(sy);
              sz = cimg::round(sz);
              print(images,"Dilate image%s with %gx%gx%g mask and neumann boundary.",
                    gmic_selection,
                    sx,sy,sz);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],dilate((unsigned int)sx,(unsigned int)sy,
                                                       (unsigned int)sz));
            } else arg_error("dilate");
            is_released = false; ++position; continue;
          }

          // Set double-sided mode for 3d rendering.
          if (!std::strcmp("-double3d",item)) {
            gmic_substitute_args();
            int value = 0;
            if (std::sscanf(argument,"%d%c",
                            &value,&end)==1) {
              is_double3d = (bool)value;
              print(images,"%s double-sided mode for 3d rendering.",
                    is_double3d?"Enable":"Disable");
            } else arg_error("double3d");
            ++position; continue;
          }

          // Patch-based smoothing.
          if (!std::strcmp("-denoise",command)) {
            gmic_substitute_args();
            float sigma_s = 10, sigma_r = 10, smoothness = 1;
            unsigned int is_fast_approximation = 0;
            float psize = 5, rsize = 6;
            if ((std::sscanf(argument,"%f%c",
                             &sigma_s,&end)==1 ||
                 std::sscanf(argument,"%f,%f%c",
                             &sigma_s,&sigma_r,&end)==2 ||
                 std::sscanf(argument,"%f,%f,%f%c",
                             &sigma_s,&sigma_r,&psize,&end)==3 ||
                 std::sscanf(argument,"%f,%f,%f,%f%c",
                             &sigma_s,&sigma_r,&psize,&rsize,&end)==4 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f%c",
                             &sigma_s,&sigma_r,&psize,&rsize,&smoothness,&end)==5 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f,%u%c",
                             &sigma_s,&sigma_r,&psize,&rsize,&smoothness,
                             &is_fast_approximation,&end)==6) &&
                sigma_s>=0 && sigma_r>=0 && psize>=0 && rsize>=0 && is_fast_approximation<=1) {
              psize = cimg::round(psize);
              rsize = cimg::round(rsize);
              print(images,"Denoise image%s using %gx%g patchs, with standard deviations %lg,%g, "
                    "lookup size %g and smoothness %g.",
                    gmic_selection,
                    psize,
                    psize,
                    sigma_s,
                    sigma_r,
                    rsize,
                    smoothness);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],blur_patch(sigma_s,sigma_r,
                                                           (unsigned int)psize,(unsigned int)rsize,
                                                           smoothness,
                                                           (bool)is_fast_approximation));
            } else arg_error("denoise");
            is_released = false; ++position; continue;
          }

          // Deriche filter.
          if (!std::strcmp("-deriche",command)) {
            gmic_substitute_args();
            unsigned int boundary = 1, order = 0;
            char sep = 0, axis = 0;
            float sigma = 0;
            if ((std::sscanf(argument,"%f,%u,%c%c",&sigma,&order,&axis,&end)==3 ||
                 (std::sscanf(argument,"%f%c,%u,%c%c",&sigma,&sep,&order,&axis,&end)==4 &&
                  sep=='%') ||
                 std::sscanf(argument,"%f,%u,%c,%u%c",&sigma,&order,&axis,&boundary,&end)==4 ||
                 (std::sscanf(argument,"%f%c,%u,%c,%u%c",
                              &sigma,&sep,&order,&axis,&boundary,&end)==5 && sep=='%')) &&
                sigma>=0 && order<=2 && (axis=='x' || axis=='y' || axis=='z' || axis=='c') &&
                boundary<=1) {
              print(images,"Apply Deriche filter on image%s, with standard "
                    "deviation %g%s, order %d, axis '%c' and %s boundary.",
                    gmic_selection,
                    sigma,sep=='%'?"%":"",
                    order,axis,
                    boundary?"neumann":"dirichlet");
              if (sep=='%') sigma = -sigma;
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],deriche(sigma,order,axis,(bool)boundary));
            } else arg_error("deriche");
            is_released = false; ++position; continue;
          }

          // Dijkstra algorithm.
          if (!std::strcmp("-dijkstra",command)) {
            gmic_substitute_args();
            float snode = 0, enode = 0;
            if (std::sscanf(argument,"%f,%f%c",&snode,&enode,&end)==2 &&
                snode>=0 && enode>=0) {
              snode = cimg::round(snode);
              enode = cimg::round(enode);
              print(images,"Compute minimal path from adjacency matri%s%s with the "
                    "Dijkstra algorithm.",
                    selection.height()>1?"ce":"x",gmic_selection);
              unsigned int off = 0;
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l] + off;
                CImg<char> name = images_names[ind].get_mark();
                if (is_get_version) {
                  CImg<T> path, dist = images[ind].get_dijkstra((unsigned int)snode,
                                                                (unsigned int)enode,path);
                  images_names.insert(name.copymark());
                  name.move_to(images_names);
                  dist.move_to(images);
                  path.move_to(images);
                } else {
                  CImg<T> path;
                  images[ind].dijkstra((unsigned int)snode,(unsigned int)enode,path);
                  images_names.insert(name.get_copymark(),ind+1);
                  name.move_to(images_names[ind]);
                  images.insert(path,ind+1);
                  ++off;
                }
              }
            } else arg_error("dijkstra");
            is_released = false; ++position; continue;
          }

          // Estimate displacement field.
          if (!std::strcmp("-displacement",command)) {
            gmic_substitute_args();
            float nb_scales = 0, nb_iterations = 10000, smoothness = 0.1f, precision = 5.0f;
            unsigned int is_backward = 1;
            CImg<unsigned int> ind;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f%c",
                             indices,&smoothness,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f%c",
                             indices,&smoothness,&precision,&end)==3 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%f%c",
                             indices,&smoothness,&precision,&nb_scales,&end)==4 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%f,%f%c",
                             indices,&smoothness,&precision,&nb_scales,&nb_iterations,&end)==5 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%f,%f,%u%c",
                             indices,&smoothness,&precision,&nb_scales,&nb_iterations,
                             &is_backward,&end)==6) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-displacement",true,
                                    false,CImg<char>::empty())).height()==1 &&
                precision>=0 && nb_scales>=0 && nb_iterations>=0 && is_backward<=1) {
              nb_scales = cimg::round(nb_scales);
              nb_iterations = cimg::round(nb_iterations);
              print(images,"Estimate displacement field from source [%u] to image%s, with "
                    "%s smoothness %g, precision %g, %g scales, %g iterations, in %s direction.",
                    *ind,
                    gmic_selection,
                    smoothness>=0?"isotropic":"anisotropic",cimg::abs(smoothness),
                    precision,
                    nb_scales,
                    nb_iterations,
                    is_backward?"backward":"forward");
              const CImg<T> source = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],displacement(source,smoothness,precision,
                                                             (unsigned int)nb_scales,
                                                             (unsigned int)nb_iterations,
                                                             (bool)is_backward));
            } else arg_error("displacement");
            is_released = false; ++position; continue;
          }

          // Display.
          if (!std::strcmp("-display",command)) {
            gmic_substitute_args();
            unsigned int X,Y,Z, XYZ[3];
            bool is_xyz = false;
            if (std::sscanf(argument,"%u,%u,%u%c",
                            &X,&Y,&Z,&end)==3) { is_xyz = true; ++position; }
            XYZ[0] = X; XYZ[1] = Y; XYZ[2] = Z;
            display_images(images,images_names,selection,is_xyz?XYZ:0);
            is_released = true; continue;
          }

          // Display 3d object.
          if (!std::strcmp("-display3d",command)) {
            display_objects3d(images,images_names,selection);
            is_released = true; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='d'.

        //----------------------------
        // Commands starting by '-e..'
        //----------------------------
        else if (command1=='e') {

          // Endif.
          if (!std::strcmp("-endif",item)) {
            const CImg<char> &s = scope.back();
            if (s[0]!='*' || s[1]!='i')
              error(images,
                    "Command 'endif': Not associated to a 'if' command within the same scope.");
            if (verbosity>0 || is_debug) print(images,"End 'if..endif' block.");
            check_elif = false;
            scope.remove();
            continue;
          }

          // Else and elif.
          if (!std::strcmp("-else",item) || (!std::strcmp("-elif",item) && !check_elif)) {
            const CImg<char> &s = scope.back();
            if (s[0]!='*' || s[1]!='i')
              error(images,
                    "Command '%s': Not associated to a 'if' command within the same scope.",
                    item);
            check_elif = false;
            if (verbosity>0 || is_debug) print(images,"Reach 'else' block.");
            for (int nb_ifs = 1; nb_ifs && position<commands_line.size(); ++position) {
              const char *const it = commands_line[position].data();
              if (!std::strcmp("-if",it)) ++nb_ifs;
              else if (!std::strcmp("-endif",it)) { if (!--nb_ifs) --position; }
            }
            continue;
          }

          // End local environment.
          if (!std::strcmp("-endlocal",item) || !std::strcmp("-endl",item)) {
            const CImg<char> &s = scope.back();
            if (s[0]!='*' || s[1]!='l')
              error(images,"Command 'endlocal': Not associated to a 'local' command within "
                    "the same scope.");
            if (verbosity>0 || is_debug) print(images,"End 'local..endlocal' block.");
            is_endlocal = true;
            break;
          }

          // Echo.
          if (!std::strcmp("-echo",command)) {
            gmic_substitute_args();
            if (verbosity>=0 || is_debug) {
              CImg<char> str(argument,std::strlen(argument)+1);
              cimg::strunescape(str);
              if (is_restriction) print(images,selection,"%s",str.data());
              else print(images,"%s",str.data());
            }
            ++position; continue;
          }

          // Exec.
          if (!std::strcmp("-exec",item)) {
            gmic_substitute_args();
#ifdef gmic_noexec
            print(images,"Execute external command '%s' (skipped, no exec allowed).",
                  argument_text);
#else // #ifdef gmic_noexec
            print(images,"Execute external command '%s'\n",
                  argument_text);
            CImg<char> arg_exec(argument,std::strlen(argument)+1);
            gmic_strreplace(arg_exec);
            const int errcode = cimg::system(arg_exec);
            cimg_snprintf(title,sizeof(title),"%d",errcode);
            CImg<char>::string(title).move_to(status);
            if (errcode) print(images,"Command '%s' returned error code '%d'.",
                               argument_text,errcode);
#endif // #ifdef gmic_noexec
            ++position; continue;
          }

          // Error.
          if (!std::strcmp("-error",command)) {
            gmic_substitute_args();
            CImg<char> str(argument,std::strlen(argument)+1);
            cimg::strunescape(str);
            if (is_restriction) error(images,selection,"%s",str.data());
            else error(images,"%s",str.data());
          }

          // Invert endianness.
          gmic_simple_item("-endian",invert_endianness,"Invert data endianness of image%s.");

#ifdef gmic_float

          // Exponential.
          gmic_simple_item("-exp",exp,"Compute pointwise exponential of image%s.");

          // Test equality.
          gmic_arithmetic_item("-eq",
                               operator_eq,
                               "Compute boolean equality between image%s and %g%s",
                               gmic_selection,value,ssep,T,
                               operator_eq,
                               "Compute boolean equality between image%s and image [%d]",
                               gmic_selection,ind[0],
                               "Compute boolean equality between image%s and expression %s'",
                               gmic_selection,argument_text,
                               "Compute boolean equality between image%s");

          // Draw ellipse.
          if (!std::strcmp("-ellipse",command)) {
            gmic_substitute_args();
            static char argR[256], argr[256];
            *argx = *argy = *argR = *argr = *color = 0;
            float x = 0, y = 0, R = 0, r = 0, angle = 0, opacity = 1;
            char sepx = 0, sepy = 0, sepR = 0, sepr = 0, seph = 0;
            unsigned int pattern = 0;
            if ((std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,argR,&end)==3 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-]%c",
                             argx,argy,argR,argr,&end)==4 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%f%c",
                             argx,argy,argR,argr,&angle,&end)==5 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%f,%f%c",
                             argx,argy,argR,argr,&angle,&opacity,&end)==6 ||
                 (std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                              "%255[0-9.eE%+-],%f,%f,0%c%x%c",
                              argx,argy,argR,argr,&angle,&opacity,&seph,&pattern,&end)==8 &&
                  seph=='x') ||
                 (std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                              "%255[0-9.eE%+-],%f,%f,%4095[0-9.eE,+-]%c",
                              argx,argy,argR,argr,&angle,&opacity,color,&end)==7 && !(pattern=0))||
                 (*color=0,std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                       "%255[0-9.eE%+-],%f,%f,0%c%x,%4095[0-9.eE,+-]%c",
                                       argx,argy,argR,argr,&angle,&opacity,&seph,&pattern,
                                       color,&end)==9 &&
                  seph=='x')) &&
                (std::sscanf(argx,"%f%c",&x,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                (std::sscanf(argy,"%f%c",&y,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                (std::sscanf(argR,"%f%c",&R,&end)==1 ||
                 (std::sscanf(argR,"%f%c%c",&R,&sepR,&end)==2 && sepR=='%')) &&
                (!*argr ||
                 std::sscanf(argr,"%f%c",&r,&end)==1 ||
                 (std::sscanf(argr,"%f%c%c",&r,&sepr,&end)==2 && sepr=='%'))) {
              if (!*argr) r = R;
              print(images,"Draw %s ellipse at (%g%s,%g%s) with radii (%g%s,%g%s) on image%s, "
                    "with orientation %g°, opacity %g and color (%s).",
                    seph=='x'?"outlined":"filled",
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    R,sepR=='%'?"%":"",
                    r,sepr=='%'?"%":"",
                    gmic_selection,
                    angle,
                    opacity,
                    *color?color:"default");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                const float rmax = std::sqrt((float)cimg::sqr(img.width()) +
                                             cimg::sqr(img.height()));
                const int
                  nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y);
                const float
                  nR = cimg::round(sepR=='%'?R*rmax/100:R),
                  nr = cimg::round(sepr=='%'?r*rmax/100:r);
                if (seph=='x') {
                  if (nR==nr) { gmic_apply(img,draw_circle(nx,ny,(int)nR,col.data(),opacity,~0U));}
                  else { gmic_apply(img,draw_ellipse(nx,ny,nR,nr,angle,col.data(),opacity,~0U)); }
                } else {
                  if (nR==nr) { gmic_apply(img,draw_circle(nx,ny,(int)nR,col.data(),opacity)); }
                  else { gmic_apply(img,draw_ellipse(nx,ny,nR,nr,angle,col.data(),opacity)); }
                }
              }
            } else arg_error("ellipse");
            is_released = false; ++position; continue;
          }

          // Equalize.
          if (!std::strcmp("-equalize",command)) {
            gmic_substitute_args();
            char sep = 0, sep0 = 0, sep1 = 0;
            double value0 = 0, value1 = 0;
            float nb_levels = 256;
            if ((std::sscanf(argument,"%f%c",
                             &nb_levels,&end)==1 ||
                 (std::sscanf(argument,"%f%c%c",
                              &nb_levels,&sep,&end)==2 && sep=='%') ||
                 std::sscanf(argument,"%f,%lf,%lf%c",
                             &nb_levels,&value0,&value1,&end)==3 ||
                 (std::sscanf(argument,"%f%c,%lf,%lf%c",
                              &nb_levels,&sep,&value0,&value1,&end)==4 && sep=='%') ||
                 (std::sscanf(argument,"%f,%lf%c,%lf%c",
                              &nb_levels,&value0,&sep0,&value1,&end)==4 && sep0=='%') ||
                 (std::sscanf(argument,"%f%c,%lf%c,%lf%c",
                              &nb_levels,&sep,&value0,&sep0,&value1,&end)==5 && sep=='%' &&
                  sep0=='%') ||
                 (std::sscanf(argument,"%f,%lf,%lf%c%c",
                              &nb_levels,&value0,&value1,&sep1,&end)==4 && sep1=='%') ||
                 (std::sscanf(argument,"%f%c,%lf,%lf%c%c",
                              &nb_levels,&sep,&value0,&value1,&sep1,&end)==5 && sep=='%' &&
                  sep1=='%') ||
                 (std::sscanf(argument,"%f,%lf%c,%lf%c%c",
                              &nb_levels,&value0,&sep0,&value1,&sep1,&end)==5 && sep0=='%' &&
                  sep1=='%') ||
                 (std::sscanf(argument,"%f%c,%lf%c,%lf%c%c",
                              &nb_levels,&sep,&value0,&sep0,&value1,&sep1,&end)==6 && sep=='%' &&
                  sep0=='%' && sep1=='%')) &&
                nb_levels>=0.5) {
              nb_levels = cimg::round(nb_levels);
              if (value0==value1 && value0==0) { value1 = 100; sep0 = sep1 = '%'; }
              print(images,"Equalize histogram of image%s, with %g%s levels in range [%g%s,%g%s].",
                    gmic_selection,
                    nb_levels,sep=='%'?"%":"",
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"");
              cimg_forY(selection,l) {
                CImg<T>& img = images[selection[l]];
                double vmin = 0, vmax = 0, nvalue0 = value0, nvalue1 = value1;
                if (sep0=='%' || sep1=='%') {
                  if (img) vmax = (double)img.max_min(vmin);
                  if (sep0=='%') nvalue0 = vmin + (vmax-vmin)*value0/100;
                  if (sep1=='%') nvalue1 = vmin + (vmax-vmin)*value1/100;
                }
                const unsigned int
                  _nb_levels = cimg::max(1U,(unsigned int)cimg::round(sep=='%'?
                                                                      nb_levels*(1+nvalue1-nvalue0)/100:
                                                                      nb_levels));
                gmic_apply(images[selection[l]],equalize(_nb_levels,(T)nvalue0,(T)nvalue1));
              }
            } else arg_error("equalize");
            is_released = false; ++position; continue;
          }

          // Erode.
          if (!std::strcmp("-erode",command)) {
            gmic_substitute_args();
            unsigned int boundary = 1, is_normalized = 0;
            float sx = 3, sy = 3, sz = 1;
            CImg<unsigned int> ind;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u%c",
                             indices,&boundary,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u%c",
                             indices,&boundary,&is_normalized,&end)==3) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-erode",true,
                                    false,CImg<char>::empty())).height()==1 &&
                boundary<=1) {
              print(images,"Erode image%s with mask [%u] and %s boundary, with%s normalization.",
                    gmic_selection,
                    *ind,
                    boundary?"neumann":"dirichlet",
                    is_normalized?"":"out");
              const CImg<T> mask = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],erode(mask,boundary,(bool)is_normalized));
            } else if ((std::sscanf(argument,"%f%c",
                                    &sx,&end)==1) &&
                       sx>=0) {
              sx = cimg::round(sx);
              print(images,"Erode image%s with mask of size %g and neumann boundary.",
                    gmic_selection,
                    sx);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],erode((unsigned int)sx));
            } else if ((std::sscanf(argument,"%f,%f%c",
                                    &sx,&sy,&end)==2 ||
                        std::sscanf(argument,"%f,%f,%f%c",
                                    &sx,&sy,&sz,&end)==3) &&
                       sx>=0 && sy>=0 && sz>=0) {
              sx = cimg::round(sx);
              sy = cimg::round(sy);
              sz = cimg::round(sz);
              print(images,"Erode image%s with %gx%gx%g mask and neumann boundary.",
                    gmic_selection,
                    sx,sy,sz);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],erode((unsigned int)sx,(unsigned int)sy,
                                                      (unsigned int)sz));
            } else arg_error("erode");
            is_released = false; ++position; continue;
          }

          // Build 3d elevation.
          if (!std::strcmp("-elevation3d",command)) {
            gmic_substitute_args();
            CImg<typename CImg<T>::Tfloat> elev;
            CImg<unsigned int> ind;
            float fact = 1;
            char sep = 0;
            *formula = 0;
            if (std::sscanf(argument,"'%4095[^']'%c",formula,&end)==1) {
              print(images,"Build 3d elevation of image%s, with elevation formula '%s'.",
                    gmic_selection,
                    formula);
              cimg_forY(selection,l) {
                CImg<T>& img = images[selection[l]];
                elev.assign(img.width(),img.height(),1,1,formula,true);
                CImgList<unsigned int> primitives;
                CImgList<float> colors;
                CImg<float> vertices = img.get_elevation3d(primitives,colors,elev);
                vertices.object3dtoCImg3d(primitives,colors);
                gmic_apply(img,replace(vertices));
              }
              ++position;
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                       sep==']' &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-elevation3d",true,
                                           false,CImg<char>::empty())).height()==1) {
              print(images,"Build 3d elevation of image%s, with elevation map [%u].",
                    gmic_selection,
                    *ind);
              if (images[*ind].spectrum()>1) images[*ind].get_norm().move_to(elev);
              else elev = gmic_image_arg(*ind);
              cimg_forY(selection,l) {
                CImg<T>& img = images[selection[l]];
                CImgList<unsigned int> primitives;
                CImgList<float> colors;
                CImg<float> vertices = img.get_elevation3d(primitives,colors,elev);
                vertices.object3dtoCImg3d(primitives,colors);
                gmic_apply(img,replace(vertices));
              }
              ++position;
            } else {
              if (std::sscanf(argument,"%f%c",
                              &fact,&end)==1) {
                print(images,"Build 3d elevation of image%s, with elevation factor %g.",
                      gmic_selection,
                      fact);
                ++position;
              } else
                print(images,"Build 3d elevation of image%s.",
                      gmic_selection);
              cimg_forY(selection,l) {
                CImg<T>& img = images[selection[l]];
                CImgList<unsigned int> primitives;
                CImgList<float> colors;
                elev.assign();
                if (fact==1 && img.spectrum()==1) elev = img.get_shared();
                else if (img.spectrum()>1) (img.get_norm().move_to(elev))*=fact;
                else (elev = img)*=fact;
                CImg<float> vertices = img.get_elevation3d(primitives,colors,elev);
                vertices.object3dtoCImg3d(primitives,colors);
                gmic_apply(img,replace(vertices));
              }
            }
            is_released = false; continue;
          }

          // Eigenvalues/eigenvectors.
          if (!std::strcmp("-eigen",command)) {
            print(images,"Compute eigen-values/vectors of symmetric matri%s or matrix field%s.",
                  selection.height()>1?"ce":"x",gmic_selection);
            CImg<float> val, vec;
            unsigned int off = 0;
            cimg_forY(selection,l) {
              const unsigned int ind = selection[l] + off;
              CImg<char> name = images_names[ind].get_mark();
              images[ind].gmic_symmetric_eigen(val,vec);
              if (is_get_version) {
                images_names.insert(name.copymark());
                name.move_to(images_names);
                val.move_to(images);
                vec.move_to(images);
              } else {
                images_names.insert(name.get_copymark(),ind+1); name.move_to(images_names[ind]);
                val.move_to(images[ind].assign()); images.insert(vec,ind+1);
                ++off;
              }
            }
            is_released = false; continue;
          }

          // Apply Eikonal PDE.
          if (!std::strcmp("-eikonal",command)) {
            gmic_substitute_args();
            float band_size = 0, nb_iter = 0;
            if ((std::sscanf(argument,"%f%c",
                             &nb_iter,&end)==1 ||
                 std::sscanf(argument,"%f,%f%c",
                             &nb_iter,&band_size,&end)==2) &&
                nb_iter>=0 && band_size>=0) {
              nb_iter = cimg::round(nb_iter);
              print(images,
                    "Apply %g iterations of eikonal equation on image%s, with band size %g.",
                    nb_iter,
                    gmic_selection,
                    band_size);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],distance_eikonal((unsigned int)nb_iter,band_size));
            } else arg_error("eikonal");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='e'.

        //----------------------------
        // Commands starting by '-f..'
        //----------------------------
        else if (command1=='f') {

#ifdef gmic_float

          // Fill.
          if (!std::strcmp("-fill",command)) {
            gmic_substitute_args();
            double value = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"%lf%c",
                            &value,&end)==1) {
              print(images,"Fill image%s with %g.",
                    gmic_selection,
                    value);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],fill((T)value));
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                       sep==']' &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-fill",true,
                                           false,CImg<char>::empty())).height()==1) {
              print(images,"Fill image%s with values from image [%u].",
                    gmic_selection,
                    *ind);
              const CImg<T> values = gmic_image_arg(*ind);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],fill(values));
            } else {
              print(images,"Fill image%s with expression '%s'.",
                    gmic_selection,
                    argument_text);
              CImg<char> arg_fill(argument,std::strlen(argument)+1);
              cimg::strpare(arg_fill,'\'',true,false);
              gmic_strreplace(arg_fill);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],fill(arg_fill.data(),true));
            }
            is_released = false; ++position; continue;
          }

          // Flood fill.
          if (!std::strcmp("-flood",command)) {
            gmic_substitute_args();
            float x = 0, y = 0, z = 0, tolerance = 0, opacity = 1;
            unsigned int is_high_connectivity = 0;
            char sepx = 0, sepy = 0, sepz = 0;
            *argx = *argy = *argz = *color = 0;
            if ((std::sscanf(argument,"%255[0-9.eE%+-]%c",
                             argx,&end)==1 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,&end)==2 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,argz,&end)==3 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f%c",
                             argx,argy,argz,&tolerance,&end)==4 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%u%c",
                             argx,argy,argz,&tolerance,&is_high_connectivity,&end)==5 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%u,%f%c",
                             argx,argy,argz,&tolerance,&is_high_connectivity,&opacity,&end)==6 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%u,%f,"
                             "%4095[0-9.eE,+-]%c",
                             argx,argy,argz,&tolerance,&is_high_connectivity,
                             &opacity,color,&end)==7) &&
                (std::sscanf(argx,"%f%c",&x,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&y,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                (!*argz ||
                 std::sscanf(argz,"%f%c",&z,&end)==1 ||
                 (std::sscanf(argz,"%f%c%c",&z,&sepz,&end)==2 && sepz=='%')) &&
                tolerance>=0) {
              print(images,
                    "Flood fill image%s from (%g%s,%g%s,%g%s), with tolerance %g, %s connectivity,"
                    "opacity %g and color (%s).",
                    gmic_selection,
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    z,sepz=='%'?"%":"",
                    tolerance,
                    is_high_connectivity?"high":"low",
                    opacity,
                    *color?color:"default");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                const int
                  nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y),
                  nz = (int)cimg::round(sepz=='%'?z*(img.depth()-1)/100:z);
                gmic_apply(img,draw_fill(nx,ny,nz,col.data(),opacity,tolerance,
                                         (bool)is_high_connectivity));
              }
            } else arg_error("flood");
            is_released = false; ++position; continue;
          }

          // Set 3d focale.
          if (!std::strcmp("-focale3d",item)) {
            gmic_substitute_args();
            float focale = 800;
            if (std::sscanf(argument,"%f%c",
                            &focale,&end)==1) {
              focale3d = focale;
              print(images,"Set 3d focale to %g.",
                    focale);
            } else arg_error("focale3d");
            ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='f'.

        //----------------------------
        // Commands starting by '-g..'
        //----------------------------
        else if (command1=='g') {

#ifdef gmic_float

          // Greater or equal.
          gmic_arithmetic_item("-ge",
                               operator_ge,
                               "Compute boolean 'greater or equal than' between image%s and %g%s",
                               gmic_selection,value,ssep,T,
                               operator_ge,
                               "Compute boolean 'greater or equal than' between image%s "
                               "and image [%d]",
                               gmic_selection,ind[0],
                               "Compute boolean 'greater or equal than' between image%s "
                               "and expression %s'",
                               gmic_selection,argument_text,
                               "Compute boolean 'greater or equal than' between image%s");

          // Greater than.
          gmic_arithmetic_item("-gt",
                               operator_gt,
                               "Compute boolean 'greater than' between image%s and %g%s",
                               gmic_selection,value,ssep,T,
                               operator_gt,
                               "Compute boolean 'greater than' between image%s and image [%d]",
                               gmic_selection,ind[0],
                               "Compute boolean 'greater than' between image%s and expression %s'",
                               gmic_selection,argument_text,
                               "Compute boolean 'greater than' between image%s");

          // Compute gradient.
          if (!std::strcmp("-gradient",command)) {
            gmic_substitute_args();
            static char axes[16];
            int scheme = 3;
            *axes = 0;
            if ((std::sscanf(argument,"%15[xyz]%c",
                             axes,&end)==1 ||
                 std::sscanf(argument,"%15[xyz],%d%c",
                             axes,&scheme,&end)==2) &&
                scheme>=-1 && scheme<=4) {
              ++position;
              print(images,"Compute gradient of image%s along axes '%s', with %s scheme.",
                    gmic_selection,
                    axes,
                    scheme==-1?"backward differences":scheme==4?"recursive":
                    scheme==1?"forward differences":scheme==2?"sobel":
                    scheme==3?"rotation invariant":"centered differences");
            } else print(images,"Compute gradient of image%s, with rotation invariant scheme.",
                         gmic_selection);
            unsigned int off = 0;
            cimg_forY(selection,l) {
              const unsigned int ind = selection[l] + off;
              CImg<T>& img = images[ind];
              CImg<char> name = images_names[ind].get_mark();
              CImgList<T> gradient = img.get_gradient(*axes?axes:0,scheme);
              if (is_get_version) {
                images_names.insert(gradient.size(),name.copymark());
                gradient.move_to(images,~0U);
              } else {
                off+=gradient.size() - 1;
                gradient[0].move_to(images[ind].assign());
                for (unsigned int i = 1; i<gradient.size(); ++i) gradient[i].move_to(images,ind+i);
                images_names[ind] = name;
                if (gradient.size()>1)
                  images_names.insert(gradient.size()-1,name.copymark(),ind+1);
              }
            }
            is_released = false; continue;
          }

          // Draw graph.
          if (!std::strcmp("-graph",command)) {
            gmic_substitute_args();
            double ymin = 0, ymax = 0, xmin = 0, xmax = 0;
            unsigned int plot_type = 1, vertex_type = 1;
            float resolution = 65536, opacity = 1;
            unsigned int pattern = ~0U;
            CImg<unsigned int> ind;
            char sep = 0, seph = 0;
            *formula = *color = 0;
            if (((std::sscanf(argument,"'%1023[^']%c%c",
                              formula,&sep,&end)==2 && sep=='\'') ||
                 std::sscanf(argument,"'%1023[^']',%f%c",
                             formula,&resolution,&end)==2 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u%c",
                             formula,&resolution,&plot_type,&end)==3 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u,%u%c",
                             formula,&resolution,&plot_type,&vertex_type,&end)==4 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf%c",
                             formula,&resolution,&plot_type,&vertex_type,&xmin,&xmax,&end)==6 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf,%lf,%lf%c",
                             formula,&resolution,&plot_type,&vertex_type,&xmin,&xmax,
                             &ymin,&ymax,&end)==8 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf,%lf,%lf,%f%c",
                             formula,&resolution,&plot_type,&vertex_type,
                             &xmin,&xmax,&ymin,&ymax,&opacity,&end)==9 ||
                 (std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf,%lf,%lf,%f,0%c%x%c",
                              formula,&resolution,&plot_type,&vertex_type,&xmin,&xmax,
                              &ymin,&ymax,&opacity,&seph,&pattern,&end)==11 && seph=='x') ||
                 (std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf,%lf,%lf,%f,%4095[0-9.eE,+-]%c",
                              formula,&resolution,&plot_type,&vertex_type,&xmin,&xmax,&ymin,&ymax,
                              &opacity,color,&end)==10 && (pattern=~0U)) ||
                 (*color=0,std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf,%lf,%lf,%f,0%c%x,"
                                       "%4095[0-9.eE,+-]%c",
                                       formula,&resolution,&plot_type,&vertex_type,&xmin,&xmax,
                                       &ymin,&ymax,&opacity,&seph,&pattern,color,&end)==12 &&
                  seph=='x')) &&
                resolution>0 && plot_type<=3 && vertex_type<=7) {
              resolution = cimg::round(resolution);
              gmic_strreplace(formula);
              print(images,
                    "Draw graph of formula '%s' on image%s, with resolution %g, %s contours, "
                    "%s vertices, x-range = (%g,%g), y-range = (%g,%g), opacity %g, "
                    "pattern 0x%x and color (%s).",
                    formula,
                    gmic_selection,
                    resolution,
                    plot_type==0?"no":plot_type==1?"linear":plot_type==2?"spline":"bar",
                    vertex_type==0?"no":vertex_type==1?"dot":vertex_type==2?"straight cross":
                    vertex_type==3?"diagonal cross":vertex_type==4?"filled circle":
                    vertex_type==5?"outlined circle":vertex_type==6?"square":"diamond",
                    xmin,xmax,
                    ymin,ymax,
                    opacity,pattern,
                    *color?color:"default");
              if (xmin==0 && xmax==0) { xmin = -4; xmax = 4; }
              if (!plot_type && !vertex_type) plot_type = 1;
              if (!resolution) resolution = 65536;
              CImg<double> values((unsigned int)resolution--); values.eval(formula);
              const double dx = xmax - xmin;
              cimg_forX(values,X) values(X) = values.eval(0,xmin+X*dx/resolution);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                gmic_apply(img,draw_graph(values,col.data(),opacity,plot_type,vertex_type,
                                          ymin,ymax,pattern));
              }
            } else if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                                     indices,&sep,&end)==2 && sep==']') ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u%c",
                                    indices,&plot_type,&end)==2 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u%c",
                                    indices,&plot_type,&vertex_type,&end)==3 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u,%lf,%lf%c",
                                    indices,&plot_type,&vertex_type,&ymin,&ymax,&end)==5 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u,%lf,%lf,%f%c",
                                    indices,&plot_type,&vertex_type,&ymin,&ymax,&opacity,&end)==6||
                        (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u,%lf,%lf,%f,0%c%x%c",
                                     indices,&plot_type,&vertex_type,&ymin,&ymax,&opacity,&seph,
                                     &pattern,&end)==8 &&
                         seph=='x') ||
                        (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u,%lf,%lf,%f,"
                                     "%4095[0-9.eE,+-]%c",
                                     indices,&plot_type,&vertex_type,&ymin,&ymax,&opacity,
                                     color,&end)==7 &&
                         (pattern=~0U)) ||
                        (*color=0,std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u,%lf,%lf,"
                                              "%f,0%c%x,%4095[0-9.eE,+-]%c",
                                              indices,&plot_type,&vertex_type,&ymin,&ymax,
                                              &opacity,&seph,&pattern,color,&end)==9 &&
                         seph=='x')) &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-graph",true,
                                           false,CImg<char>::empty())).height()==1 &&
                       plot_type<=3 && vertex_type<=7) {
              if (!plot_type && !vertex_type) plot_type = 1;
              print(images,"Draw graph of dataset [%u] on image%s, with %s contours, %s vertices, "
                    "y-range = (%g,%g), opacity %g, pattern 0x%x and color (%s).",
                    *ind,
                    gmic_selection,
                    plot_type==0?"no":plot_type==1?"linear":plot_type==2?"spline":"bar",
                    vertex_type==0?"no":vertex_type==1?"dot":vertex_type==2?"straight cross":
                    vertex_type==3?"diagonal cross":vertex_type==4?"filled circle":
                    vertex_type==5?"outlined circle":vertex_type==6?"square":"diamond",
                    ymin,ymax,
                    opacity,pattern,
                    *color?color:"default");
              const CImg<T> values = gmic_image_arg(*ind);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                gmic_apply(img,draw_graph(values,col.data(),opacity,plot_type,vertex_type,
                                          ymin,ymax,pattern));
              }
            } else arg_error("graph");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='g'.

        //----------------------------
        // Commands starting by '-h..'
        //----------------------------
        else if (command1=='h') {

#ifdef gmic_float

          // Histogram.
          if (!std::strcmp("-histogram",command)) {
            gmic_substitute_args();
            char sep = 0, sep0 = 0, sep1 = 0;
            double value0 = 0, value1 = 0;
            float nb_levels = 256;
            if ((std::sscanf(argument,"%f%c",
                             &nb_levels,&end)==1 ||
                 (std::sscanf(argument,"%f%c%c",
                              &nb_levels,&sep,&end)==2 && sep=='%') ||
                 std::sscanf(argument,"%f,%lf,%lf%c",
                             &nb_levels,&value0,&value1,&end)==3 ||
                 (std::sscanf(argument,"%f%c,%lf,%lf%c",
                              &nb_levels,&sep,&value0,&value1,&end)==4 && sep=='%') ||
                 (std::sscanf(argument,"%f,%lf%c,%lf%c",
                              &nb_levels,&value0,&sep0,&value1,&end)==4 && sep0=='%') ||
                 (std::sscanf(argument,"%f%c,%lf%c,%lf%c",
                              &nb_levels,&sep,&value0,&sep0,&value1,&end)==5 && sep=='%' &&
                  sep0=='%') ||
                 (std::sscanf(argument,"%f,%lf,%lf%c%c",
                              &nb_levels,&value0,&value1,&sep1,&end)==4 && sep1=='%') ||
                 (std::sscanf(argument,"%f%c,%lf,%lf%c%c",
                              &nb_levels,&sep,&value0,&value1,&sep1,&end)==5 && sep=='%' &&
                  sep1=='%') ||
                 (std::sscanf(argument,"%f,%lf%c,%lf%c%c",
                              &nb_levels,&value0,&sep0,&value1,&sep1,&end)==5 && sep0=='%' &&
                  sep1=='%') ||
                 (std::sscanf(argument,"%f%c,%lf%c,%lf%c%c",
                              &nb_levels,&sep,&value0,&sep0,&value1,&sep1,&end)==6 && sep=='%' &&
                  sep0=='%' && sep1=='%')) &&
                nb_levels>0) {
              nb_levels = cimg::round(nb_levels);
              if (value0==value1 && value0==0) { value1 = 100; sep0 = sep1 = '%'; }
              print(images,"Compute histogram of image%s, using %g%s level%s in range [%g%s,%g%s].",
                    gmic_selection,
                    nb_levels,sep=='%'?"%":"",
                    nb_levels>1?"s":"",
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                double vmin = 0, vmax = 0, nvalue0 = value0, nvalue1 = value1;
                if (sep0=='%' || sep1=='%') {
                  if (img) vmax = (double)img.max_min(vmin);
                  if (sep0=='%') nvalue0 = vmin + (vmax-vmin)*value0/100;
                  if (sep1=='%') nvalue1 = vmin + (vmax-vmin)*value1/100;
                }
                const unsigned int
                  _nb_levels = cimg::max(1U,(unsigned int)cimg::round(sep=='%'?
                                                                      nb_levels*(1+nvalue1-nvalue0)/100:
                                                                      nb_levels));
                gmic_apply(images[selection[l]],histogram(_nb_levels,(T)nvalue0,(T)nvalue1));
              }
            } else arg_error("histogram");
            is_released = false; ++position; continue;
          }

          // HSI to RGB.
          gmic_simple_item("-hsi2rgb",HSItoRGB,"Convert image%s from HSI to RGB color bases.");

          // HSL to RGB.
          gmic_simple_item("-hsl2rgb",HSLtoRGB,"Convert image%s from HSL to RGB color bases.");

          // HSV to RGB.
          gmic_simple_item("-hsv2rgb",HSVtoRGB,"Convert image%s from HSV to RGB color bases.");

          // Compute Hessian.
          if (!std::strcmp("-hessian",command)) {
            gmic_substitute_args();
            static char axes[64];
            *axes = 0;
            if (std::sscanf(argument,"%63[xyz]%c",
                            axes,&end)==1) {
              ++position;
              print(images,"Compute Hessian of image%s along axes '%s'.",
                    gmic_selection,
                    axes);
            } else
              print(images,"Compute Hessian of image%s.",
                    gmic_selection);
            unsigned int off = 0;
            cimg_forY(selection,l) {
              const unsigned int ind = selection[l] + off;
              CImg<T>& img = images[ind];
              CImg<char> name = images_names[ind].get_mark();
              CImgList<T> hessian = img.get_hessian(*axes?axes:0);
              if (is_get_version) {
                images_names.insert(hessian.size(),name.copymark());
                hessian.move_to(images,~0U);
              } else {
                off+=hessian.size() - 1;
                hessian[0].move_to(images[ind].assign());
                for (unsigned int i = 1; i<hessian.size(); ++i) hessian[i].move_to(images,ind+i);
                images_names[ind] = name;
                if (hessian.size()>1) images_names.insert(hessian.size()-1,name.copymark(),ind+1);
              }
            }
            is_released = false; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='h'.

        //----------------------------
        // Commands starting by '-i..'
        //----------------------------
        else if (command1=='i' && !(command[2]=='f' && !command[3])) {   // (Skip for '-if').

#ifdef gmic_float

          // Draw image.
          if (!std::strcmp("-image",command)) {
            gmic_substitute_args();
            char sep = 0, sepx = 0, sepy = 0, sepz = 0, sepc = 0, indicesm[256];
            float x = 0, y = 0, z = 0, c = 0, opacity = 1, max_opacity_mask = 1;
            CImg<unsigned int> ind, indm;
            *indices = *indicesm = *argx = *argy = *argz = *argc = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-]%c",
                             indices,argx,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             indices,argx,argy,&end)==3 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-]%c",
                             indices,argx,argy,argz,&end)==4 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-]%c",
                             indices,argx,argy,argz,argc,&end)==5 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%255[0-9.eE%+-],%f%c",
                             indices,argx,argy,argz,argc,&opacity,&end)==6 ||
                 (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                              "%255[0-9.eE%+-],%255[0-9.eE%+-],%f,[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,argx,argy,argz,argc,&opacity,indicesm,&sep,&end)==8 &&
                  sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%255[0-9.eE%+-],%f,[%255[a-zA-Z0-9_.%+-]],%f%c",
                             indices,argx,argy,argz,argc,&opacity,indicesm,
                             &max_opacity_mask,&end)==8) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-image",true,
                                    false,CImg<char>::empty())).height()==1 &&
                (!*indicesm ||
                 (indm = selection2cimg(indicesm,images.size(),images_names,"-image",true,
                                        false,CImg<char>::empty())).height()==1) &&
                (!*argx ||
                 std::sscanf(argx,"%f%c",&x,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&y,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                (!*argz ||
                 std::sscanf(argz,"%f%c",&z,&end)==1 ||
                 (std::sscanf(argz,"%f%c%c",&z,&sepz,&end)==2 && sepz=='%')) &&
                (!*argc ||
                 std::sscanf(argc,"%f%c",&c,&end)==1 ||
                 (std::sscanf(argc,"%f%c%c",&c,&sepc,&end)==2 && sepc=='%'))) {
              const CImg<T> sprite = gmic_image_arg(*ind);
              CImg<T> mask;
              if (indm) {
                mask = gmic_image_arg(*indm);
                print(images,"Draw image [%u] at (%g%s,%g%s,%g%s,%g%s) on image%s, "
                      "with opacity %g and mask [%u].",
                      *ind,
                      x,sepx=='%'?"%":"",
                      y,sepy=='%'?"%":"",
                      z,sepz=='%'?"%":"",
                      c,sepc=='%'?"%":"",
                      gmic_selection,
                      opacity,
                      *indm);
              } else print(images,"Draw image [%u] at (%g%s,%g%s,%g%s,%g%s) on image%s, "
                           "with opacity %g.",
                           *ind,
                           x,sepx=='%'?"%":"",
                           y,sepy=='%'?"%":"",
                           z,sepz=='%'?"%":"",
                           c,sepc=='%'?"%":"",
                           gmic_selection,
                           opacity);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y),
                  nz = (int)cimg::round(sepz=='%'?z*(img.depth()-1)/100:z),
                  nc = (int)cimg::round(sepc=='%'?c*(img.spectrum()-1)/100:c);
                if (indm) {
                  gmic_apply(img,draw_image(nx,ny,nz,nc,sprite,mask,opacity,max_opacity_mask));
                } else {
                  gmic_apply(img,draw_image(nx,ny,nz,nc,sprite,opacity));
                }
              }
            } else arg_error("image");
            is_released = false; ++position; continue;
          }

          // Index image with a LUT.
          if (!std::strcmp("-index",command)) {
            gmic_substitute_args();
            unsigned int lut_type = 0, map_indexes = 0;
            float dithering = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                            indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f%c",
                             indices,&dithering,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%u%c",
                             indices,&dithering,&map_indexes,&end)==3) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-index",true,
                                    false,CImg<char>::empty())).height()==1) {
              const float ndithering = dithering<0?0:dithering>1?1:dithering;
              print(images,"Index values in image%s by LUT [%u], with dithering level %g%s.",
                    gmic_selection,
                    *ind,
                    ndithering,
                    map_indexes?" and index mapping":"");
              const CImg<T> palette = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],index(palette,ndithering,(bool)map_indexes));
            } else if ((std::sscanf(argument,"%u%c",&lut_type,&end)==1 ||
                        std::sscanf(argument,"%u,%f%c",&lut_type,&dithering,&end)==2 ||
                        std::sscanf(argument,"%u,%f,%u%c",
                                    &lut_type,&dithering,&map_indexes,&end)==3) &&
                       lut_type<=7) {
              const float ndithering = dithering<0?0:dithering>1?1:dithering;
              print(images,"Index values in image%s by %s color LUT, with dithering level %g%s.",
                    gmic_selection,
                    lut_type==0?"default":lut_type==1?"HSV":lut_type==2?"lines":lut_type==3?"hot":
                    lut_type==4?"cool":lut_type==5?"jet":lut_type==6?"flag":"cube",
                    ndithering,map_indexes?" and index mapping":"");
              const CImg<T>
                palette = lut_type==0?CImg<T>::default_LUT256():lut_type==1?CImg<T>::HSV_LUT256():
                lut_type==2?CImg<T>::lines_LUT256():lut_type==3?CImg<T>::hot_LUT256():
                lut_type==4?CImg<T>::cool_LUT256():lut_type==5?CImg<T>::jet_LUT256():
                lut_type==6?CImg<T>::flag_LUT256():CImg<T>::cube_LUT256();
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],index(palette,ndithering,(bool)map_indexes));
            } else arg_error("index");
            is_released = false; ++position; continue;
          }

          // Matrix inverse.
          gmic_simple_item("-invert",invert,"Invert matrix image%s.");

          // Extract 3d isoline.
          if (!std::strcmp("-isoline3d",command)) {
            gmic_substitute_args();
            float x0 = -3, y0 = -3, x1 = 3, y1 = 3, value = 0, dx = 256, dy = 256;
            char sep = 0, sepx = 0, sepy = 0;
            *formula = 0;
            if (std::sscanf(argument,"%f%c",
                            &value,&end)==1 ||
                std::sscanf(argument,"%f%c%c",
                            &value,&sep,&end)==2) {
              print(images,"Extract 3d isolines from image%s, using isovalue %g%s.",
                    gmic_selection,
                    value,sep=='%'?"%":"");
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                CImg<T>& img = images[ind];
                if (img) {
                  CImg<float> vertices;
                  CImgList<unsigned int> primitives;
                  CImgList<unsigned char> colors;
                  CImg<unsigned char> palette;
                  palette.assign(3,img.spectrum(),1,1,220).noise(35,1);
                  if (img.spectrum()==1) palette(0) = palette(1) = palette(2) = 200;
                  else {
                    palette(0,0) = 255; palette(1,0) = palette(2,0) = 30;
                    palette(0,1) = palette(2,1) = 30; palette(1,1) = 255;
                    if (img.spectrum()>=3) palette(0,2) = palette(1,2) = 30; palette(2,2) = 255;
                  }
                  cimg_forC(img,k) {
                    const CImg<T> channel = img.get_shared_channel(k);
                    float nvalue = value;
                    if (sep=='%') {
                      float vmin = 0, vmax = (float)channel.max_min(vmin);
                      nvalue = vmin + (vmax-vmin)*value/100;
                    }
                    CImgList<unsigned int> prims;
                    const CImg<float> pts = img.get_shared_channel(k).get_isoline3d(prims,nvalue);
                    vertices.append_object3d(primitives,pts,prims);
                    colors.insert(prims.size(),CImg<unsigned char>::vector(palette(0,k),
                                                                           palette(1,k),
                                                                           palette(2,k)));
                  }
                  if (!vertices)
                    warn(images,"Command 'isoline3d': Isovalue %g%s not found in image [%u].",
                         value,sep=='%'?"%":"",ind);
                  vertices.object3dtoCImg3d(primitives,colors);
                  gmic_apply(img,replace(vertices));
                } else { gmic_apply(img,replace(img)); }
              }
            } else if ((std::sscanf(argument,"'%4095[^']',%f%c",
                                    formula,&value,&end)==2 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f%c",
                                    formula,&value,&x0,&y0,&x1,&y1,&end)==6 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f%c",
                                    formula,&value,&x0,&y0,&x1,&y1,&dx,&dy,&end)==8 ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f%c,%f%c",
                                     formula,&value,&x0,&y0,&x1,&y1,&dx,&sepx,&dy,&end)==9 &&
                         sepx=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f%c%c",
                                     formula,&value,&x0,&y0,&x1,&y1,&dx,&dy,&sepy,&end)==9 &&
                         sepy=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f%c,%f%c%c",
                                     formula,&value,&x0,&y0,&x1,&y1,&dx,&sepx,&dy,&sepy,&end)==10&&
                         sepx=='%' && sepy=='%')) &&
                       dx>0 && dy>0) {
              dx = cimg::round(dx);
              dy = cimg::round(dy);
              gmic_strreplace(formula);
              print(images,"Extract 3d isoline %g from formula '%s', in range (%g,%g)-(%g,%g) "
                    "with size %g%sx%g%s.",
                    value,
                    formula,
                    x0,y0,
                    x1,y1,
                    dx,sepx=='%'?"%":"",
                    dy,sepy=='%'?"%":"");
              if (sepx=='%') dx = -dx;
              if (sepy=='%') dy = -dy;
              CImgList<unsigned int> primitives;
              CImg<T> vertices = CImg<T>::isoline3d(primitives,(const char*)formula,value,
                                                    x0,y0,x1,y1,(int)dx,(int)dy);
              vertices.object3dtoCImg3d(primitives).move_to(images);
              cimg_snprintf(title,sizeof(title),"[3d isoline %g of '%s']",value,formula);
              gmic_ellipsize(title,sizeof(title));
              CImg<char>::string(title).move_to(images_names);
            } else arg_error("isoline3d");
            is_released = false; ++position; continue;
          }

          // Extract 3d isosurface.
          if (!std::strcmp("-isosurface3d",command)) {
            gmic_substitute_args();
            float x0 = -3, y0 = -3, z0 = -3, x1 = 3, y1 = 3, z1 = 3, value = 0,
              dx = 32, dy = 32, dz = 32;
            char sep = 0, sepx = 0, sepy = 0, sepz = 0;
            *formula = 0;
            if (std::sscanf(argument,"%f%c",
                            &value,&end)==1 ||
                std::sscanf(argument,"%f%c%c",
                            &value,&sep,&end)==2) {
              print(images,"Extract 3d isosurface from image%s, using isovalue %g%s.",
                    gmic_selection,
                    value,sep=='%'?"%":"");
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                CImg<T>& img = images[ind];
                if (img) {
                  CImg<float> vertices;
                  CImgList<unsigned int> primitives;
                  CImgList<unsigned char> colors;
                  CImg<unsigned char> palette;
                  palette.assign(3,img.spectrum(),1,1,220).noise(35,1);
                  if (img.spectrum()==1) palette(0) = palette(1) = palette(2) = 200;
                  else {
                    palette(0,0) = 255; palette(1,0) = palette(2,0) = 30;
                    palette(0,1) = palette(2,1) = 30; palette(1,1) = 255;
                    if (img.spectrum()>=3) palette(0,2) = palette(1,2) = 30; palette(2,2) = 255;
                  }
                  cimg_forC(img,k) {
                    const CImg<T> channel = img.get_shared_channel(k);
                    float nvalue = value;
                    if (sep=='%') {
                      float vmin = 0, vmax = (float)channel.max_min(vmin);
                      nvalue = vmin + (vmax-vmin)*value/100;
                    }
                    CImgList<unsigned int> prims;
                    const CImg<float> pts = channel.get_isosurface3d(prims,nvalue);
                    vertices.append_object3d(primitives,pts,prims);
                    colors.insert(prims.size(),CImg<unsigned char>::vector(palette(0,k),
                                                                           palette(1,k),
                                                                           palette(2,k)));
                  }
                  if (!vertices) {
                    if (img.depth()>1)
                      warn(images,
                           "Command 'isosurface3d': Isovalue %g%s not found in image [%u].",
                           value,sep=='%'?"%":"",ind);
                    else
                      warn(images,
                           "Command 'isosurface3d': Image [%u] has a single slice, "
                           "isovalue %g%s not found.",
                           ind,value,sep=='%'?"%":"");
                  }
                  vertices.object3dtoCImg3d(primitives,colors);
                  gmic_apply(img,replace(vertices));
                } else { gmic_apply(img,replace(img)); }
              }
            } else if ((std::sscanf(argument,"'%4095[^']',%f%c",
                                    formula,&value,&end)==2 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f%c",
                                    formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,&end)==8 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f,%f,%f%c",
                                    formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,&dx,&dy,&dz,&end)==11 ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f%c,%f,%f%c",
                                     formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,
                                     &dx,&sepx,&dy,&dz,&end)==12 &&
                         sepx=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f,%f%c,%f%c",
                                     formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,
                                     &dx,&dy,&sepy,&dz,&end)==12 &&
                         sepy=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f,%f,%f%c%c",
                                     formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,
                                     &dx,&dy,&dz,&sepz,&end)==12 &&
                         sepz=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f%c,%f%c,%f%c",
                                     formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,
                                     &dx,&sepx,&dy,&sepy,&dz,&end)==13 &&
                         sepx=='%' && sepy=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f%c,%f,%f%c%c",
                                     formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,
                                     &dx,&sepx,&dy,&dz,&sepz,&end)==13 &&
                         sepx=='%' && sepz=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f,%f%c,%f%c%c",
                                     formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,
                                     &dx,&dy,&sepy,&dz,&sepz,&end)==13 &&
                         sepy=='%' && sepz=='%') ||
                        (std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%f,%f,%f%c,%f%c,%f%c%c",
                                     formula,&value,&x0,&y0,&z0,&x1,&y1,&z1,
                                     &dx,&sepx,&dy,&sepy,&dz,&sepz,&end)==14 &&
                         sepx=='%' && sepy=='%' && sepz=='%')) &&
                       dx>0 && dy>0 && dz>0) {
              dx = cimg::round(dx);
              dy = cimg::round(dy);
              dz = cimg::round(dz);
              gmic_strreplace(formula);
              print(images,"Extract 3d isosurface %g from formula '%s', "
                    "in range (%g,%g,%g)-(%g,%g,%g) with size %g%sx%g%sx%g%s.",
                    value,
                    formula,
                    x0,y0,z0,
                    x1,y1,z1,
                    dx,sepx=='%'?"%":"",
                    dy,sepy=='%'?"%":"",
                    dz,sepz=='%'?"%":"");
              if (sepx=='%') dx = -dx;
              if (sepy=='%') dy = -dy;
              if (sepz=='%') dz = -dz;
              CImgList<unsigned int> primitives;
              CImg<T> vertices = CImg<T>::isosurface3d(primitives,(const char*)formula,value,
                                                       x0,y0,z0,x1,y1,z1,(int)dx,(int)dy,(int)dz);
              vertices.object3dtoCImg3d(primitives).move_to(images);
              cimg_snprintf(title,sizeof(title),"[3d isosurface %g of '%s']",value,formula);
              gmic_ellipsize(title,sizeof(title));
              CImg<char>::string(title).move_to(images_names);
            } else arg_error("isosurface3d");
            is_released = false; ++position; continue;
          }

          // Inpaint.
          if (!std::strcmp("-inpaint",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                sep==']' &&
                (ind=selection2cimg(indices,images.size(),images_names,"-inpaint",true,
                                    false,CImg<char>::empty())).height()==1) {
              print(images,"Inpaint image%s with mask [%u].",
                    gmic_selection,
                    *ind);
              const CImg<T> mask = gmic_image_arg(*ind);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],inpaint(mask));
            } else arg_error("inpaint");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='i'.

        //----------------------------
        // Commands starting by '-k..'
        //----------------------------
        else if (command1=='k') {

          // Keep images.
          if (!std::strcmp("-keep",command)) {
            print(images,"Keep image%s",
                  gmic_selection);
            CImgList<T> _images, nimages(selection.height());
            CImgList<char> _images_names, nimages_names(selection.height());
            if (is_get_version) { _images.assign(images); _images_names.assign(images_names); }
            cimg_forY(selection,l) {
              nimages[l].swap(images[selection[l]]);
              nimages_names[l].swap(images_names[selection[l]]);
            }
            nimages.move_to(images);
            nimages_names.move_to(images_names);
            if (is_get_version) {
              _images.move_to(images,0);
              _images_names.move_to(images_names,0);
            }
            if (verbosity>=0 || is_debug) {
              std::fprintf(cimg::output()," (%u image%s left).",
                           images.size(),images.size()==1?"":"s");
              std::fflush(cimg::output());
            }
            is_released = false; continue;
          }

        } // command1=='k'.

        //----------------------------
        // Commands starting by '-l..'
        //----------------------------
        else if (command1=='l') {

          // Start local environnement.
          if (!std::strcmp("-local",command)) {
            CImg<char>::string("*local").move_to(scope);
            if (verbosity>0 || is_debug)
              print(images,"Start 'local..endlocal' block, with image%s.",
                    gmic_selection);
            CImgList<T> nimages(selection.height());
            CImgList<char> nimages_names(selection.height());
            if (is_get_version) cimg_forY(selection,l) {
                nimages[l].assign(images[selection[l]]);
                nimages_names[l].assign(images_names[selection[l]]);
              } else cimg_forY(selection,l) {
                if (images[selection[l]].is_shared())
                  nimages[l] = CImg<T>(images[selection[l]],true);
                else nimages[l].swap(images[selection[l]]);
                nimages_names[l].swap(images_names[selection[l]]);
              }
            const unsigned int local_scope_size = scope.size();
            CImg<char> exception_message, exception_command;
            try {
              parse(commands_line,position,nimages,nimages_names,variables_sizes);
            } catch (gmic_exception &e) {
              int nb_locals = 0;
              for (nb_locals = 1; nb_locals && position<commands_line.size(); ++position) {
                const char *const it = commands_line[position].data();
                if (!std::strcmp("-local",it) || !std::strcmp("-l",it) ||
                    !std::strcmp("--local",it) || !std::strcmp("--l",it) ||
                    !std::strncmp("-local[",it,7) || !std::strncmp("-l[",it,3) ||
                    !std::strncmp("--local[",it,8) || !std::strncmp("--l[",it,4)) ++nb_locals;
                else if (!std::strcmp("-endlocal",it) || !std::strcmp("-endl",it)) --nb_locals;
                else if (nb_locals==1 && !std::strcmp("-onfail",it)) break;
              }
              if (scope.size()>local_scope_size) scope.remove(local_scope_size,scope.size()-1);
              if (nb_locals==1 && position<commands_line.size()) { // Onfail block found.
                if (verbosity>0 || is_debug) print(images,"Reach 'onfail' block.");
                parse(commands_line,++position,nimages,nimages_names,variables_sizes);
              } else { // Onfail block not found.
                exception_message.assign(e._message);
                exception_command.assign(e._command);
              }
            }
            scope.remove();
            if (is_get_version) {
              nimages.move_to(images,~0U);
              cimglist_for(nimages_names,l) nimages_names[l].copymark();
              nimages_names.move_to(images_names,~0U);
            } else {
              const unsigned int nb = cimg::min((unsigned int)selection.height(),nimages.size());
              if (nb>0) {
                for (unsigned int i = 0; i<nb; ++i) {
                  if (images[selection[i]].is_shared()) {
                    images[selection[i]] = nimages[i];
                    nimages[i].assign();
                  } else images[selection[i]].swap(nimages[i]);
                  images_names[selection[i]].swap(nimages_names[i]);
                }
                nimages.remove(0,nb-1);
                nimages_names.remove(0,nb-1);
              }
              if (nb<(unsigned int)selection.height())
                remove_images(images,images_names,selection,nb,selection.height()-1);
              else if (nimages) {
                const unsigned int ind0 = selection?selection.back()+1:images.size();
                images.insert(nimages,ind0);
                nimages_names.move_to(images_names,ind0);
              }
            }
            if (exception_message || exception_command)
              throw gmic_exception(exception_command.data(),exception_message.data());
            continue;
          }

#ifdef gmic_float

          // Less or equal.
          gmic_arithmetic_item("-le",
                               operator_le,"Compute boolean 'less or equal than' between image%s "
                               "and %g%s",
                               gmic_selection,value,ssep,T,
                               operator_le,"Compute boolean 'less or equal than' between image%s "
                               "and image [%d]",
                               gmic_selection,ind[0],
                               "Compute boolean 'less or equal than' between image%s and "
                               "expression %s'",
                               gmic_selection,argument_text,
                               "Compute boolean 'less or equal than' between image%s");

          // Less than.
          gmic_arithmetic_item("-lt",
                               operator_lt,
                               "Compute boolean 'less than' between image%s and %g%s",
                               gmic_selection,value,ssep,T,
                               operator_lt,
                               "Compute boolean 'less than' between image%s and image [%d]",
                               gmic_selection,ind[0],
                               "Compute boolean 'less than' between image%s and expression %s'",
                               gmic_selection,argument_text,
                               "Compute boolean 'less than' between image%s");

          // Logarithm, base-e.
          gmic_simple_item("-log",log,"Compute pointwise base-e logarithm of image%s.");

          // Logarithm, base-2.
          gmic_simple_item("-log2",log2,"Compute pointwise base-2 logarithm of image%s.");

          // Logarithm, base-10.
          gmic_simple_item("-log10",log10,"Compute pointwise base-10 logarithm of image%s.");

          // Draw line.
          if (!std::strcmp("-line",command)) {
            gmic_substitute_args();
            static char argx1[256], argy1[256];
            *argx = *argy = *argx1 = *argy1 = *color = 0;
            float x0 = 0, y0 = 0, x1 = 0, y1 = 0, opacity = 1;
            char sepx0 = 0, sepy0 = 0, sepx1 = 0, sepy1 = 0, seph = 0;
            unsigned int pattern = ~0U;
            if ((std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-]%c",
                             argx,argy,argx1,argy1,&end)==4 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%f%c",
                             argx,argy,argx1,argy1,&opacity,&end)==5 ||
                 (std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                              "%255[0-9.eE%+-],%f,0%c%x%c",
                              argx,argy,argx1,argy1,&opacity,&seph,&pattern,&end)==7 &&
                  seph=='x') ||
                 (std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                              "%255[0-9.eE%+-],%f,%4095[0-9.eE,+-]%c",
                              argx,argy,argx1,argy1,&opacity,color,&end)==6 && (pattern=~0U)) ||
                 (*color=0,std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                       "%255[0-9.eE%+-],%f,0%c%x,%4095[0-9.eE,+-]%c",
                                       argx,argy,argx1,argy1,&opacity,&seph,
                                       &pattern,color,&end)==8 && seph=='x')) &&
                (std::sscanf(argx,"%f%c",&x0,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x0,&sepx0,&end)==2 && sepx0=='%')) &&
                (std::sscanf(argy,"%f%c",&y0,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y0,&sepy0,&end)==2 && sepy0=='%')) &&
                (std::sscanf(argx1,"%f%c",&x1,&end)==1 ||
                 (std::sscanf(argx1,"%f%c%c",&x1,&sepx1,&end)==2 && sepx1=='%')) &&
                (std::sscanf(argy1,"%f%c",&y1,&end)==1 ||
                 (std::sscanf(argy1,"%f%c%c",&y1,&sepy1,&end)==2 && sepy1=='%'))) {
              print(images,"Draw line (%g%s,%g%s) - (%g%s,%g%s) on image%s, with opacity %g, "
                    "pattern 0x%x and color (%s).",
                    x0,sepx0=='%'?"%":"",
                    y0,sepy0=='%'?"%":"",
                    x1,sepx1=='%'?"%":"",
                    y1,sepy1=='%'?"%":"",
                    gmic_selection,
                    opacity,pattern,
                    *color?color:"default");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                const int
                  nx0 = (int)cimg::round(sepx0=='%'?x0*(img.width()-1)/100:x0),
                  ny0 = (int)cimg::round(sepy0=='%'?y0*(img.height()-1)/100:y0),
                  nx1 = (int)cimg::round(sepx1=='%'?x1*(img.width()-1)/100:x1),
                  ny1 = (int)cimg::round(sepy1=='%'?y1*(img.height()-1)/100:y1);
                gmic_apply(img,draw_line(nx0,ny0,nx1,ny1,col.data(),opacity,pattern));
              }
            } else arg_error("line");
            is_released = false; ++position; continue;
          }

          // Lab to RGB
          gmic_simple_item("-lab2rgb",LabtoRGB,"Convert image%s from Lab to RGB color bases.");

          // Label connected components.
          if (!std::strcmp("-label",command)) {
            gmic_substitute_args();
            unsigned int is_high_connectivity = 0;
            float tolerance = 0;
            if ((std::sscanf(argument,"%f%c",&tolerance,&end)==1 ||
                 std::sscanf(argument,"%f,%u%c",&tolerance,&is_high_connectivity,&end)==2) &&
                tolerance>=0) {
              print(images,
                    "Label connected components on image%s, with tolerance %g and "
                    "%s connectivity.",
                    gmic_selection,tolerance,is_high_connectivity?"high":"low");
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],label((bool)is_high_connectivity,tolerance));
            } else arg_error("label");
            is_released = false; ++position; continue;
          }

          // Set 3d light position.
          if (!std::strcmp("-light3d",item)) {
            gmic_substitute_args();
            float lx = 0, ly = 0, lz = -5e8;
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"%f,%f,%f%c",
                            &lx,&ly,&lz,&end)==3) {
              print(images,"Set 3d light position to (%g,%g,%g).",
                    lx,ly,lz);
              light3d_x = lx;
              light3d_y = ly;
              light3d_z = lz;
              ++position;
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                       sep==']' &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-light3d",true,
                                           false,CImg<char>::empty())).height()==1) {
              print(images,"Set 3d light texture from image [%u].",*ind);
              light3d = images[*ind];
              ++position;
            } else {
              print(images,"Reset 3d light to default.");
              light3d.assign();
              light3d_x = light3d_y = 0; light3d_z = -5e8;
            }
            continue;
          }

#endif // #ifdef gmic_float
        } // command1=='l'.

        //----------------------------
        // Commands starting by '-m..'
        //----------------------------
        else if (command1=='m') {

          // Move images.
          if (!std::strcmp("-move",command)) {
            gmic_substitute_args();
            float pos = 0;
            char sep = 0;
            if (std::sscanf(argument,"%f%c",&pos,&end)==1 ||
                (std::sscanf(argument,"%f%c%c",&pos,&sep,&end)==2 && sep=='%')) {
              const int
                _ind0 = (int)cimg::round(sep=='%'?pos*images.size()/100:pos),
                ind0 = _ind0<0?_ind0+(int)images.size():_ind0;
              if (ind0<0 || ind0>(int)images.size())
                error(images,"Command 'move': Invalid position '%d' (not in range -%u..%u).",
                      _ind0,images.size(),images.size()-1);
              print(images,"Move image%s to position %d.",
                    gmic_selection,
                    ind0);
              CImgList<T> _images, nimages;
              CImgList<char> _images_names, nimages_names;
              if (is_get_version) {
                _images.insert(images.size());
                // Copy original list while preserving shared state of each item.
                cimglist_for(_images,l) _images[l].assign(images[l],images[l].is_shared());
                _images_names.assign(images_names);
              }
              nimages.insert(selection.height());
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (is_get_version) images[ind].move_to(nimages[l]);
                else images[ind].swap(nimages[l]);
                // Empty shared image as a special item to be removed later.
                images[ind]._is_shared = true;
                images_names[ind].move_to(nimages_names);
              }
              images.insert(nimages.size(),ind0);
              cimglist_for(nimages,l) nimages[l].swap(images[ind0+l]);
              nimages_names.move_to(images_names,ind0);
              cimglist_for(images,l) if (!images[l] && images[l].is_shared()) {
                images.remove(l); images_names.remove(l--); // Remove special items.
              }
              if (is_get_version) {
                cimglist_for(images,l) // Replace shared items by non-shared one for a get version.
                  if (images[l].is_shared()) {
                    CImg<T> tmp; (images[l].move_to(tmp)).swap(images[l]);
                  }
                images.insert(_images.size(),0);
                cimglist_for(_images,l) images[l].swap(_images[l]);
                _images_names.move_to(images_names,0);
              }
            } else arg_error("move");
            is_released = false; ++position; continue;
          }

          // Mirror.
          if (!std::strcmp("-mirror",command)) {
            gmic_substitute_args();
            bool is_valid_argument = true;
            for (const char *s = argument; *s; ++s) {
              const char _s = *s;
              if (_s!='x' && _s!='y' && _s!='z' && _s!='c') { is_valid_argument = false; break; }
            }
            if (*argument && is_valid_argument) {
              print(images,"Mirror image%s along the '%s'-ax%cs.",
                    gmic_selection,
                    argument_text,
                    std::strlen(argument)>1?'e':'i');
              cimg_forY(selection,l) gmic_apply(images[selection[l]],mirror(argument));
            } else arg_error("mirror");
            is_released = false; ++position; continue;
          }

#ifdef gmic_float

          // Multiplication.
          gmic_arithmetic_item("-mul",
                               operator*=,
                               "Multiply image%s by %g%s",
                               gmic_selection,value,ssep,double,
                               mul,
                               "Multiply image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Multiply image%s by expression %s",
                               gmic_selection,argument_text,
                               "Multiply image%s");
          // Modulo.
          gmic_arithmetic_item("-mod",
                               operator%=,
                               "Compute pointwise modulo of image%s by %g%s",
                               gmic_selection,value,ssep,T,
                               operator%=,
                               "Compute pointwise modulo of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute pointwise modulo of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential pointwise modulo of image%s");

          // Max.
          gmic_arithmetic_item("-max",
                               max,
                               "Compute pointwise maximum between image%s and %g%s",
                               gmic_selection,value,ssep,T,
                               max,
                               "Compute pointwise maximum between image%s and image [%d]",
                               gmic_selection,ind[0],
                               "Compute pointwise maximum between image%s and expression %s",
                               gmic_selection,argument_text,
                               "Compute pointwise maximum of all image%s together");
          // Min.
          gmic_arithmetic_item("-min",
                               min,
                               "Compute pointwise minimum between image%s and %g%s",
                               gmic_selection,value,ssep,T,
                               min,
                               "Compute pointwise minimum between image%s and image [%d]",
                               gmic_selection,ind[0],
                               "Compute pointwise minimum between image%s and expression %s",
                               gmic_selection,argument_text,
                               "Compute pointwise minimum of image%s");

          // Matrix multiplication.
          gmic_arithmetic_item("-mmul",
                               operator*=,
                               "Multiply matrix/vector%s by %g%s",
                               gmic_selection,value,ssep,double,
                               operator*=,
                               "Multiply matrix/vector%s by matrix/vector image [%d]",
                               gmic_selection,ind[0],
                               "Multiply matrix/vector%s by expression %s",
                               gmic_selection,argument_text,
                               "Multiply matrix/vector%s");

          // Set 3d rendering modes.
          if (!std::strcmp("-mode3d",item)) {
            gmic_substitute_args();
            int value = 0;
            if (std::sscanf(argument,"%d%c",
                            &value,&end)==1 &&
                value>=-1 && value<=5) {
              render3d = value;
              print(images,"Set static 3d rendering mode to %s.",
                    render3d==-1?"bounding-box":
                    render3d==0?"pointwise":render3d==1?"linear":render3d==2?"flat":
                    render3d==3?"flat-shaded":render3d==4?"Gouraud-shaded":
                    render3d==5?"Phong-shaded":"none");
            } else arg_error("mode3d");
            ++position; continue;
          }

          if (!std::strcmp("-moded3d",item)) {
            gmic_substitute_args();
            int value = 0;
            if (std::sscanf(argument,"%d%c",
                            &value,&end)==1 &&
                value>=-1 && value<=5) {
              renderd3d = value;
              print(images,"Set dynamic 3d rendering mode to %s.",
                    renderd3d==-1?"bounding-box":
                    renderd3d==0?"pointwise":renderd3d==1?"linear":renderd3d==2?"flat":
                    renderd3d==3?"flat-shaded":renderd3d==4?"Gouraud-shaded":
                    renderd3d==5?"Phong-shaded":"none");
            } else arg_error("moded3d");
            ++position; continue;
          }

          // Map LUT.
          if (!std::strcmp("-map",command)) {
            gmic_substitute_args();
            unsigned int lut_type = 0;
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                sep==']' &&
                (ind=selection2cimg(indices,images.size(),images_names,"-map",true,
                                    false,CImg<char>::empty())).height()==1) {
              print(images,"Map LUT [%u] on image%s.",
                    *ind,
                    gmic_selection);
              const CImg<T> palette = gmic_image_arg(*ind);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],map(palette));
            } else if (std::sscanf(argument,"%u%c",&lut_type,&end)==1 &&
                       lut_type<=7) {
              print(images,"Map %s color LUT on image%s.",
                    lut_type==0?"default":lut_type==1?"HSV":lut_type==2?"lines":lut_type==3?"hot":
                    lut_type==4?"cool":lut_type==5?"jet":lut_type==6?"flag":"cube",
                    gmic_selection);
              const CImg<T>
                palette = lut_type==0?CImg<T>::default_LUT256():lut_type==1?CImg<T>::HSV_LUT256():
                lut_type==2?CImg<T>::lines_LUT256():lut_type==3?CImg<T>::hot_LUT256():
                lut_type==4?CImg<T>::cool_LUT256():lut_type==5?CImg<T>::jet_LUT256():
                lut_type==6?CImg<T>::flag_LUT256():CImg<T>::cube_LUT256();
              cimg_forY(selection,l) gmic_apply(images[selection[l]],map(palette));
            } else arg_error("map");
            is_released = false; ++position; continue;
          }

          // Median filter.
          if (!std::strcmp("-median",command)) {
            gmic_substitute_args();
            float siz = 3;
            if (std::sscanf(argument,"%f%c",
                            &siz,&end)==1 &&
                siz>=0) {
              siz = cimg::round(siz);
              print(images,"Apply median filter of size %g, on image%s.",
                    siz,
                    gmic_selection);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],blur_median((unsigned int)siz));
            } else arg_error("median");
            is_released = false; ++position; continue;
          }

          // Matrix division.
          gmic_arithmetic_item("-mdiv",
                               operator/=,
                               "Divide matrix/vector%s by %g%s",
                               gmic_selection,value,ssep,double,
                               operator/=,
                               "Divide matrix/vector%s by matrix/vector image [%d]",
                               gmic_selection,ind[0],
                               "Divide matrix/vector%s by expression %s",
                               gmic_selection,argument_text,
                               "Divide matrix/vector%s");

          // MSE.
          if (!std::strcmp("-mse",command)) {
            print(images,"Compute the %dx%d matrix of MSE values, from image%s.",
                  selection.height(),selection.height(),
                  gmic_selection);
            if (selection) {
              CImgList<T> subimages(selection.height());
              cimg_forY(selection,l) subimages[l].assign(images[selection[l]],true);
              CImg<T> img(subimages.size(),subimages.size(),1,1,(T)0);
              cimg_forXY(img,x,y) if (x>y) img(x,y) = img(y,x) = (T)subimages[x].MSE(subimages[y]);
              CImg<char> name = CImg<char>::string("[MSE]");
              if (is_get_version) {
                img.move_to(images);
                name.move_to(images_names);
              } else {
                remove_images(images,images_names,selection,1,selection.height()-1);
                img.move_to(images[selection[0]].assign());
                name.move_to(images_names[selection[0]]);
              }
            }
            is_released = false; continue;
          }

          // Draw mandelbrot/julia fractal.
          if (!std::strcmp("-mandelbrot",command)) {
            gmic_substitute_args();
            double z0r = -2, z0i = -2, z1r = 2, z1i = 2, paramr = 0, parami = 0;
            unsigned int is_julia = 0;
            float opacity = 1, itermax = 100;
            if ((std::sscanf(argument,"%lf,%lf,%lf,%lf%c",
                             &z0r,&z0i,&z1r,&z1i,&end)==4 ||
                 std::sscanf(argument,"%lf,%lf,%lf,%lf,%f%c",
                             &z0r,&z0i,&z1r,&z1i,&itermax,&end)==5 ||
                 std::sscanf(argument,"%lf,%lf,%lf,%lf,%f,%u%c",
                             &z0r,&z0i,&z1r,&z1i,&itermax,&is_julia,&end)==6 ||
                 std::sscanf(argument,"%lf,%lf,%lf,%lf,%f,%u,%lf,%lf%c",
                             &z0r,&z0i,&z1r,&z1i,&itermax,&is_julia,&paramr,
                             &parami,&end)==8 ||
                 std::sscanf(argument,"%lf,%lf,%lf,%lf,%f,%u,%lf,%lf,%f%c",
                             &z0r,&z0i,&z1r,&z1i,&itermax,&is_julia,
                             &paramr,&parami,&opacity,&end)==9) &&
                itermax>=0 && is_julia<=1) {
              itermax = cimg::round(itermax);
              print(images,"Draw %s fractal on image%s, from complex area (%g,%g)-(%g,%g) "
                    "with c0 = (%g,%g) and %g iterations.",
                    is_julia?"julia":"mandelbrot",
                    gmic_selection,
                    z0r,z0i,
                    z1r,z1i,
                    paramr,parami,
                    itermax);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],draw_mandelbrot(CImg<T>(),opacity,z0r,z0i,z1r,z1i,
                                                                (unsigned int)itermax,true,
                                                                (bool)is_julia,
                                                                paramr,parami));
            } else arg_error("mandelbrot");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='m'.

        //----------------------------
        // Commands starting by '-n..'
        //----------------------------
        else if (command1=='n') {

          // Set image name.
          if (!std::strcmp("-name",command)) {
            gmic_substitute_args();
            const unsigned int l = std::strlen(argument);
            CImg<char> name(argument,l+1);
            unsigned int is_modified=0;
            if (l>=2 && name[l-2]==',' && (name[l-1]=='0' || name[l-1]=='1')) {
              is_modified = name[l-1]!='0';
              name[l-2] = 0;
            }
            print(images,"Set name of image%s to '%s'%s.",
                  gmic_selection,name.data(),is_modified?" (modified)":"");
            gmic_strreplace(name);
            if (is_modified) name.mark();
            cimg_forY(selection,l) images_names[selection[l]].assign(name);
            ++position; continue;
          }

#ifdef gmic_float

          // Normalize.
          if (!std::strcmp("-normalize",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind0, ind1;
            double value0 = 0, value1 = 0;
            char sep0 = 0, sep1 = 0;
            *argx = *argy = 0;
            if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                            argx,argy,&end)==2 &&
                ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                  sep0==']' &&
                  (ind0=selection2cimg(indices,images.size(),images_names,"-normalize",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 (std::sscanf(argx,"%lf%c%c",&value0,&sep0,&end)==2 && sep0=='%') ||
                 std::sscanf(argx,"%lf%c",&value0,&end)==1) &&
                ((std::sscanf(argy,"[%255[a-zA-Z0-9_.%+-]%c%c",formula,&sep1,&end)==2 &&
                  sep1==']' &&
                  (ind1=selection2cimg(formula,images.size(),images_names,"-normalize",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 (std::sscanf(argy,"%lf%c%c",&value1,&sep1,&end)==2 && sep1=='%') ||
                 std::sscanf(argy,"%lf%c",&value1,&end)==1)) {
              if (ind0) { value0 = images[*ind0].min(); sep0 = 0; }
              if (ind1) { value1 = images[*ind1].max(); sep1 = 0; }
              print(images,"Normalize image%s in range [%g%s,%g%s].",
                    gmic_selection,
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                double vmin = 0, vmax = 0, nvalue0 = value0, nvalue1 = value1;
                if (sep0=='%' || sep1=='%') {
                  if (img) vmax = (double)img.max_min(vmin);
                  if (sep0=='%') nvalue0 = vmin + (vmax-vmin)*value0/100;
                  if (sep1=='%') nvalue1 = vmin + (vmax-vmin)*value1/100;
                }
                gmic_apply(img,normalize((T)nvalue0,(T)nvalue1));
              }
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                       sep0==']' &&
                       (ind0=selection2cimg(indices,images.size(),images_names,"-normalize",true,
                                            false,CImg<char>::empty())).height()==1) {
              if (images[*ind0]) value1 = (double)images[*ind0].max_min(value0);
              print(images,"Normalize image%s in range [%g,%g].",
                    gmic_selection,
                    value0,
                    value1);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],normalize((T)value0,(T)value1));
            } else arg_error("normalize");
            is_released = false; ++position; continue;
          }

          // Test difference.
          gmic_arithmetic_item("-neq",
                               operator_neq,
                               "Compute boolean inequality between image%s and %g%s",
                               gmic_selection,value,ssep,T,
                               operator_neq,
                               "Compute boolean inequality between image%s and image [%d]",
                               gmic_selection,ind[0],
                               "Compute boolean inequality between image%s and expression %s'",
                               gmic_selection,argument_text,
                               "Compute boolean inequality between image%s");

          // Add noise.
          if (!std::strcmp("-noise",command)) {
            gmic_substitute_args();
            int noise_type = 0;
            float sigma = 0;
            char sep = 0;
            if ((std::sscanf(argument,"%f%c",
                             &sigma,&end)==1 ||
                 (std::sscanf(argument,"%f%c%c",
                              &sigma,&sep,&end)==2 && sep=='%') ||
                 std::sscanf(argument,"%f,%d%c",
                             &sigma,&noise_type,&end)==2 ||
                 (std::sscanf(argument,"%f%c,%d%c",
                              &sigma,&sep,&noise_type,&end)==3 && sep=='%')) &&
                sigma>=0 && noise_type>=0 && noise_type<=4) {
              const char *st_type = noise_type==0?"gaussian":
                noise_type==1?"uniform":
                noise_type==2?"salt&pepper":
                noise_type==3?"poisson":"rice";
              if (sep=='%') sigma = -sigma;
              print(images,"Add %s noise to image%s, with standard deviation %g%s.",
                    st_type,
                    gmic_selection,
                    cimg::abs(sigma),sep=='%'?"%":"");
              cimg_forY(selection,l) gmic_apply(images[selection[l]],noise(sigma,noise_type));
            } else arg_error("noise");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='n'.

        //----------------------------
        // Commands starting by '-o..'
        //----------------------------
        else if (command1=='o') {

          // Output.
          if (!std::strcmp("-output",command)) {
            gmic_substitute_args();
            static char cext[8], _filename[4096], filename_tmp[512], options[256];
            *cext = *_filename = *filename_tmp = *options = 0;
            if (std::sscanf(argument,"%8[a-zA-Z]:%4095[^,],%255s",cext,_filename,options)<2 ||
                !cext[1]) {  // length of 'ext' must be >=2 (avoid case 'C:\\..' on Windows).
              *cext = *_filename = *options = 0;
              if (std::sscanf(argument,"%4095[^,],%255s",_filename,options)!=2) {
                std::strncpy(_filename,argument,sizeof(_filename)-1);
                _filename[sizeof(_filename)-1] = 0;
              }
            }
            gmic_strreplace(_filename);
            gmic_strreplace(options);

            if (*cext) { // Force output to be written as a '.ext' file : generate random filename.
              if (*_filename=='-' && (!_filename[1] || _filename[1]=='.')) {
                // Simplify filename 'ext:-.foo' as '-.ext'.
                cimg_snprintf(_filename,sizeof(_filename),"-.%s",cext);
                *cext = 0;
              } else {
                std::FILE *file = 0;
                do {
                  cimg_snprintf(filename_tmp,sizeof(filename_tmp),"%s%c%s.%s",
                                cimg::temporary_path(),cimg_file_separator,
                                cimg::filenamerand(),cext);
                  if ((file=std::fopen(filename_tmp,"rb"))!=0) std::fclose(file);
                } while (file);
              }
            }
            const char
              *const filename = *cext?filename_tmp:_filename,
              *const ext = cimg::split_filename(filename);

            if (!cimg::strcasecmp(ext,"off")) {
              static char nfilename[4096];
              *nfilename = 0;
              std::strncpy(nfilename,filename,sizeof(nfilename)-1);
              nfilename[sizeof(nfilename)-1] = 0;
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (selection.height()!=1) cimg::number_filename(filename,l,6,nfilename);
                if (!images[ind].is_CImg3d(true,message))
                  error(images,
                        "Command 'output': 3d object file '%s', invalid 3d object [%u] "
                        "in selected image%s (%s).",
                        nfilename,ind,gmic_selection,message);
                print(images,"Output 3d object [%u] as file '%s'.",
                      ind,
                      nfilename);
                CImgList<unsigned int> primitives;
                CImgList<float> colors, opacities;
                CImg<float> vertices(images[ind]);
                vertices.CImg3dtoobject3d(primitives,colors,opacities).
                  save_off(primitives,colors,nfilename);
              }
            } else if (!cimg::strcasecmp(ext,"tiff") || !cimg::strcasecmp(ext,"tif")) {
              float _compression = 0;
              if (std::sscanf(options,"%f%c",&_compression,&end)!=1) _compression = 0;
              if (_compression<0) _compression = 0; else if (_compression>6) _compression = 6;
              const unsigned int compression = (unsigned int)cimg::round(_compression);
              CImgList<T> output_images(selection.height());
              cimg_forY(selection,l) output_images[l].assign(images[selection[l]],true);
              if (output_images.size()==1)
                print(images,"Output image%s as file '%s', with %s compression "
                      "(1 image %dx%dx%dx%d).",
                      gmic_selection,
                      _filename,
                      compression==0?"no":compression==1?"CCITTRLE":compression==2?"CCITT4":
                      compression==3?"CCITT6":compression==4?"LZW":compression==5?"JPEG1":"JPEG2",
                      output_images[0].width(),output_images[0].height(),
                      output_images[0].depth(),output_images[0].spectrum());
              else print(images,"Output image%s as file '%s', with %s compression.",
                         gmic_selection,
                         _filename,
                         compression==0?"no":compression==1?"CCITTRLE":compression==2?"CCITT4":
                         compression==3?"CCITT6":compression==4?"LZW":compression==5?"JPEG1":
                         "JPEG2");
              if (!output_images)
                error(images,"Command 'output': File '%s', instance list (%u,%p) is empty.",
                      _filename,output_images.size(),output_images.data());
              if (output_images.size()==1) output_images[0].save_tiff(filename,compression);
              else output_images.save_tiff(filename,compression);
            } else if (!cimg::strcasecmp(ext,"gif")) {
              float _fps = 0, _nb_loops = 0;
              CImgList<T> output_images(selection.height());
              cimg_forY(selection,l) output_images[l].assign(images[selection[l]],true);
              if (output_images.size()>1 && std::sscanf(options,"%f,%f",&_fps,&_nb_loops)>=1) {
                // Save animated .gif file.
                const unsigned int
                  fps = (unsigned int)cimg::round(_fps),
                  nb_loops = (unsigned int)cimg::round(_nb_loops);
                if (nb_loops)
                  print(images,
                        "Output image%s as animated file '%s', with %u fps and %u loops.",
                        gmic_selection,_filename,fps,nb_loops);
                else
                  print(images,
                        "Output image%s as animated file '%s', with %u fps.",
                        gmic_selection,_filename,fps);
                output_images.save_gif_external(filename,fps,nb_loops);
              } else {
                if (output_images.size()==1)
                  print(images,"Output image%s as file '%s' (1 image %dx%dx%dx%d).",
                        gmic_selection,
                        _filename,
                        output_images[0].width(),output_images[0].height(),
                        output_images[0].depth(),output_images[0].spectrum());
                else print(images,"Output image%s as file '%s'.",
                           gmic_selection,
                           _filename);
                output_images.save(filename); // Save distinct .gif files.
              }
            } else if (!cimg::strcasecmp(ext,"jpeg") || !cimg::strcasecmp(ext,"jpg")) {
              float quality = 100;
              if (std::sscanf(options,"%f%c",&quality,&end)!=1) quality = 100;
              if (quality<0) quality = 0; else if (quality>100) quality = 100;
              CImgList<T> output_images(selection.height());
              cimg_forY(selection,l) output_images[l].assign(images[selection[l]],true);
              if (output_images.size()==1)
                print(images,
                      "Output image%s as file '%s', with quality %g%% (1 image %dx%dx%dx%d).",
                      gmic_selection,
                      _filename,
                      quality,
                      output_images[0].width(),output_images[0].height(),
                      output_images[0].depth(),output_images[0].spectrum());
              else print(images,"Output image%s as file '%s', with quality %g%%.",
                         gmic_selection,
                         _filename,
                         quality);
              if (!output_images)
                error(images,"Command 'output': File '%s', instance list (%u,%p) is empty.",
                      _filename,output_images.size(),output_images.data());
              if (output_images.size()==1)
                output_images[0].save_jpeg(filename,(unsigned int)cimg::round(quality));
              else {
                char nfilename[4096];
                cimglist_for(output_images,l) {
                  cimg::number_filename(filename,l,6,nfilename);
                  output_images[l].save_jpeg(nfilename,(unsigned int)cimg::round(quality));
                }
              }
            } else if (!cimg::strcasecmp(ext,"mnc") && *options) {
              CImgList<T> output_images(selection.height());
              cimg_forY(selection,l) output_images[l].assign(images[selection[l]],true);
              if (output_images.size()==1)
                print(images,
                      "Output image%s as file '%s', with header get from file '%s' "
                      "(1 image %dx%dx%dx%d).",
                      gmic_selection,
                      _filename,
                      options,
                      output_images[0].width(),output_images[0].height(),
                      output_images[0].depth(),output_images[0].spectrum());
              else
                print(images,
                      "Output image%s as file '%s', with header get from file '%s'.",
                      gmic_selection,
                      _filename,
                      options);
              if (output_images.size()==1)
                output_images[0].save_minc2(filename,options);
              else {
                char nfilename[4096];
                cimglist_for(output_images,l) {
                  cimg::number_filename(filename,l,6,nfilename);
                  output_images[l].save_minc2(nfilename,options);
                }
              }
            } else if (!cimg::strcasecmp(ext,"raw")) {
              const char *const stype = std::sscanf(options,"%255[A-zA-Z]%c",argx,&end)==1?argx:
                cimg::type<T>::string();
              CImgList<T> output_images(selection.height());
              cimg_forY(selection,l) output_images[l].assign(images[selection[l]],true);
              if (output_images.size()==1)
                print(images,
                      "Output image%s as file '%s', with pixel type '%s' (1 image %dx%dx%dx%d).",
                      gmic_selection,
                      _filename,
                      stype,
                      output_images[0].width(),output_images[0].height(),
                      output_images[0].depth(),output_images[0].spectrum());
              else print(images,"Output image%s as file '%s', with pixel type '%s'.",
                         gmic_selection,
                         _filename,
                         stype);
              if (!output_images)
                error(images,"Command 'output': File '%s', instance list (%u,%p) is empty.",
                      _filename,output_images.size(),output_images.data());

#define gmic_save_raw(value_type,svalue_type)                           \
              if (!std::strcmp(stype,svalue_type)) {                    \
                if (output_images.size()==1)                            \
                  CImg<value_type>(output_images[0]).save_raw(filename); \
                else {                                                  \
                  static char nfilename[4096];                          \
                  cimglist_for(output_images,l) {                       \
                    cimg::number_filename(filename,l,6,nfilename);      \
                    CImg<value_type>(output_images[l]).save_raw(nfilename); \
                  }                                                     \
                }                                                       \
              }
              gmic_save_raw(bool,"bool")
              else gmic_save_raw(unsigned char,"uchar")
                else gmic_save_raw(unsigned char,"unsigned char")
                  else gmic_save_raw(char,"char")
                    else gmic_save_raw(unsigned short,"ushort")
                      else gmic_save_raw(unsigned short,"unsigned short")
                        else gmic_save_raw(short,"short")
                          else gmic_save_raw(unsigned int,"uint")
                            else gmic_save_raw(unsigned short,"unsigned int")
                              else gmic_save_raw(int,"int")
                                else gmic_save_raw(float,"float")
                                  else gmic_save_raw(double,"double")
                                    else error(images,
                                               "Command 'output': File '%s', invalid specified "
                                               "pixel type '%s'.",
                                               _filename,stype);
            } else
              if (!cimg::strcasecmp(ext,"avi") || !cimg::strcasecmp(ext,"mov") ||
                  !cimg::strcasecmp(ext,"asf") || !cimg::strcasecmp(ext,"divx") ||
                  !cimg::strcasecmp(ext,"flv") || !cimg::strcasecmp(ext,"mpg") ||
                  !cimg::strcasecmp(ext,"m1v") || !cimg::strcasecmp(ext,"m2v") ||
                  !cimg::strcasecmp(ext,"m4v") || !cimg::strcasecmp(ext,"mjp") ||
                  !cimg::strcasecmp(ext,"mkv") || !cimg::strcasecmp(ext,"mpe") ||
                  !cimg::strcasecmp(ext,"movie") || !cimg::strcasecmp(ext,"ogm") ||
                  !cimg::strcasecmp(ext,"qt") || !cimg::strcasecmp(ext,"rm") ||
                  !cimg::strcasecmp(ext,"vob") || !cimg::strcasecmp(ext,"wmv") ||
                  !cimg::strcasecmp(ext,"xvid") || !cimg::strcasecmp(ext,"mpeg") ||
                  !cimg::strcasecmp(ext,"ogg")) {
                float fps = 0, bitrate = 0;
                std::sscanf(options,"%f,%f",&fps,&bitrate);
                fps = cimg::round(fps);
                bitrate = cimg::round(bitrate);
                if (!fps) fps = 25;
                if (!bitrate) bitrate = 2048;
                CImgList<T> output_images(selection.height());
                cimg_forY(selection,l) output_images[l].assign(images[selection[l]],true);
                print(images,"Output image%s as file '%s', with %g fps and bitrate %gk.",
                      gmic_selection,
                      _filename,
                      fps,bitrate);
                if (!output_images)
                  error(images,"Command 'output': File '%s, instance list (%u,%p) is empty.",
                        _filename,output_images.size(),output_images.data());
                output_images.save_ffmpeg(filename,(unsigned int)fps,(unsigned int)bitrate);
              } else {
                CImgList<T> output_images(selection.height());
                cimg_forY(selection,l) output_images[l].assign(images[selection[l]],true);
                if (output_images.size()==1)
                  print(images,"Output image%s as file '%s' (1 image %dx%dx%dx%d).",
                        gmic_selection,
                        _filename,
                        output_images[0].width(),output_images[0].height(),
                        output_images[0].depth(),output_images[0].spectrum());
                else print(images,"Output image%s as file '%s'.",
                           gmic_selection,
                           _filename);
                output_images.save(filename);
              }

            if (*cext) { // When output forced to 'ext' : copy final file to specified location.
              try {
                CImg<unsigned char>::get_load_raw(filename_tmp).save_raw(_filename);
                std::remove(filename_tmp);
              } catch (...) {
                error(images,
                      "Command 'output': Invalid write of file '%s from temporary file '%s'.",
                      _filename,filename_tmp);
              }
            }
            is_released = true; ++position; continue;
          }

          // Exception handling in local environments.
          if (!std::strcmp("-onfail",item)) {
            const CImg<char> &s = scope.back();
            if (s[0]!='*' || s[1]!='l')
              error(images,"Command 'onfail': Not associated to a 'local' command within "
                    "the same scope.");
            for (int nb_locals = 1; nb_locals && position<commands_line.size(); ++position) {
              const char *const it = commands_line[position].data();
              if (!std::strcmp("-local",it) || !std::strcmp("-l",it) ||
                  !std::strcmp("--local",it) || !std::strcmp("--l",it) ||
                  !std::strncmp("-local[",it,7) || !std::strncmp("-l[",it,3) ||
                  !std::strncmp("--local[",it,8) || !std::strncmp("--l[",it,4)) ++nb_locals;
              else if (!std::strcmp("-endlocal",it) || !std::strcmp("-endl",it)) {
                --nb_locals; if (!nb_locals) --position;
              }
            }
            continue;
          }

#ifdef gmic_float

          // Draw 3d object.
          if (!std::strcmp("-object3d",command)) {
            gmic_substitute_args();
            float x = 0, y = 0, z = 0, opacity = 1;
            char sep = 0, sepx = 0, sepy = 0;
            unsigned int
              is_zbuffer = 1,
              _render3d = (unsigned int)cimg::max(0,render3d),
              _is_double3d = is_double3d?1:0;
            float
              _focale3d = focale3d,
              _light3d_x = light3d_x,
              _light3d_y = light3d_y,
              _light3d_z = light3d_z,
              _specular_lightness3d = specular_lightness3d,
              _specular_shininess3d = specular_shininess3d;
            CImg<unsigned int> ind;
            *argx = *argy = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-]%c",
                             indices,argx,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             indices,argx,argy,&end)==3 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f%c",
                             indices,argx,argy,&z,&end)==4 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f,%f%c",
                             indices,argx,argy,&z,&opacity,&end)==5 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f,%f,%u%c",
                             indices,argx,argy,&z,&opacity,&_render3d,&end)==6 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f,%f,%u,%u%c",
                             indices,argx,argy,&z,&opacity,&_render3d,&_is_double3d,&end)==7 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f,%f,%u,%u,%u%c",
                             indices,argx,argy,&z,&opacity,&_render3d,&_is_double3d,&is_zbuffer,
                             &end)==8 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f,%f,%u,%u,%u,%f%c",
                             indices,argx,argy,&z,&opacity,&_render3d,&_is_double3d,&is_zbuffer,
                             &_focale3d,&end)==9 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f,%f,%u,%u,%u,%f,%f,%f,%f%c",
                             indices,argx,argy,&z,&opacity,&_render3d,&_is_double3d,&is_zbuffer,
                             &_focale3d,&_light3d_x,&_light3d_y,&_light3d_z,&end)==12 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f,%f,%u,%u,%u,%f,%f,%f,%f,%f,%f%c",
                             indices,argx,argy,&z,&opacity,&_render3d,&_is_double3d,&is_zbuffer,
                             &_focale3d,&_light3d_x,&_light3d_y,&_light3d_z,
                             &_specular_lightness3d,&_specular_shininess3d,&end)==14) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-object3d",true,
                                    false,CImg<char>::empty())).height()==1 &&
                (!*argx ||
                 std::sscanf(argx,"%f%c",&x,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&y,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                _render3d<=5 && is_zbuffer<=1 && _is_double3d<=1) {
              if (!images[*ind].is_CImg3d(true,message))
                error(images,"Command 'object3d': Invalid 3d object [%u], specified "
                      "in argument '%s' (%s).",
                      *ind,argument_text,message);
              print(images,"Draw 3d object [%u] at (%g%s,%g%s,%g) on image%s, with opacity %g, "
                    "%s rendering, %s-sided mode, %sz-buffer, focale %g, 3d light at (%g,%g,%g) "
                    "and specular properties (%g,%g)",
                    *ind,
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    z,
                    gmic_selection,
                    opacity,
                    _render3d==0?"dot":_render3d==1?"wireframe":_render3d==2?"flat":
                    _render3d==3?"flat-shaded":_render3d==4?"gouraud-shaded":"phong-shaded",
                    _is_double3d?"double":"simple",
                    is_zbuffer?"":"no ",
                    _focale3d,_light3d_x,_light3d_y,_light3d_z,
                    _specular_lightness3d,_specular_shininess3d);
              CImgList<unsigned int> primitives;
              CImgList<float> colors, opacities;
              CImgList<unsigned char> _colors;  // 'uchar' colors when rendering with light.
              CImg<float> vertices = images[*ind];
              if (_render3d>=3) {
                vertices.CImg3dtoobject3d(primitives,_colors,opacities);
                if (light3d) _colors.insert(light3d,~0U,true);
              } else vertices.CImg3dtoobject3d(primitives,colors,opacities);
              cimglist_for(opacities,o) if (!opacities[o].is_shared()) opacities[o]*=opacity;

              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const float
                  nx = sepx=='%'?x*(img.width()-1)/100:x,
                  ny = sepy=='%'?y*(img.height()-1)/100:y;
                CImg<float> zbuffer(is_zbuffer?img.width():0,is_zbuffer?img.height():0,1,1,0);
                if (colors) {
                  gmic_apply(img,draw_object3d(nx,ny,z,vertices,primitives,colors,opacities,
                                               _render3d,_is_double3d,_focale3d,
                                               _light3d_x,_light3d_y,_light3d_z,
                                               _specular_lightness3d,_specular_shininess3d,
                                               zbuffer));
                } else {
                  gmic_apply(img,draw_object3d(nx,ny,z,vertices,primitives,_colors,opacities,
                                               _render3d,_is_double3d,_focale3d,
                                               _light3d_x,_light3d_y,_light3d_z,
                                               _specular_lightness3d,_specular_shininess3d,
                                               zbuffer));
                }
              }
            } else arg_error("object3d");
            is_released = false; ++position; continue;
          }

          // Bitwise or.
          gmic_arithmetic_item("-or",
                               operator|=,
                               "Compute bitwise OR of image%s by %g%s",
                               gmic_selection,value,ssep,T,
                               operator|=,
                               "Compute bitwise OR of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute bitwise OR of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential bitwise OR of image%s");

          // Set 3d object opacity.
          if (!std::strcmp("-opacity3d",command)) {
            gmic_substitute_args();
            float opacity = 1;
            if (std::sscanf(argument,"%f%c",
                            &opacity,&end)==1) {
              print(images,"Set opacity of 3d object%s to %g.",
                    gmic_selection,
                    opacity);
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (!images[ind].is_CImg3d(true,message))
                  error(images,"Command 'opacity3d': Invalid 3d object [%d], "
                        "in selected image%s (%s).",
                        ind,gmic_selection,message);
                gmic_apply(images[ind],color_CImg3d(0,0,0,opacity,false,true));
              }
            } else arg_error("opacity3d");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='o'.

        //----------------------------
        // Commands starting by '-p..'
        //----------------------------
        else if (command1=='p') {

          // Permute axes.
          if (!std::strcmp("-permute",command)) {
            gmic_substitute_args();
            print(images,"Permute axes of image%s, with permutation '%s'.",
                  gmic_selection,argument_text);
            cimg_forY(selection,l) gmic_apply(images[selection[l]],permute_axes(argument));
            is_released = false; ++position; continue;
          }

          // Set progress indice.
          if (!std::strcmp("-progress",item)) {
            gmic_substitute_args();
            float value = -1;
            if (std::sscanf(argument,"%f%c",
                            &value,&end)==1) {
              if (value<0) value = -1; else if (value>100) value = 100;
              if (value>=0)
                print(images,"Set progress indice to %g%%.",
                      value);
              else
                print(images,"Disable progress indice.");
              *progress = value;
            } else arg_error("progress");
            ++position; continue;
          }

          // Print.
          if (!std::strcmp("-print",command)) {
            print_images(images,images_names,selection);
            is_released = true; continue;
          }

#ifdef gmic_float

          // Power.
          gmic_arithmetic_item("-pow",
                               pow,
                               "Compute image%s to the power of %g%s",
                               gmic_selection,value,ssep,double,
                               pow,
                               "Compute image%s to the power of image [%d]",
                               gmic_selection,ind[0],
                               "Compute image%s to the power of expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential power of image%s");

          // Draw point.
          if (!std::strcmp("-point",command)) {
            gmic_substitute_args();
            float x = 0, y = 0, z = 0, opacity = 1;
            char sepx = 0, sepy = 0, sepz = 0;
            *argx = *argy = *argz = *color = 0;
            if ((std::sscanf(argument,"%255[0-9.eE%+-]%c",
                             argx,&end)==1 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,&end)==2 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,argz,&end)==3 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f%c",
                             argx,argy,argz,&opacity,&end)==4 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,"
                             "%4095[0-9.eE,+-]%c",
                             argx,argy,argz,&opacity,color,&end)==5) &&
                (std::sscanf(argx,"%f%c",&x,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&y,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                (!*argz ||
                 std::sscanf(argz,"%f%c",&z,&end)==1 ||
                 (std::sscanf(argz,"%f%c%c",&z,&sepz,&end)==2 && sepz=='%'))) {
              print(images,
                    "Draw point (%g%s,%g%s,%g%s) on image%s, with opacity %g and color (%s).",
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    z,sepz=='%'?"%":"",
                    gmic_selection,
                    opacity,
                    *color?color:"default");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                const int
                  nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y),
                  nz = (int)cimg::round(sepz=='%'?z*(img.depth()-1)/100:z);
                gmic_apply(img,draw_point(nx,ny,nz,col.data(),opacity));
              }
            } else arg_error("point");
            is_released = false; ++position; continue;
          }

          // Draw polygon.
          if (!std::strcmp("-polygon",command)) {
            gmic_substitute_args();
            static char strint[256];
            *strint = *color = 0;
            float N = 0, x0 = 0, y0 = 0, opacity = 1;
            char sepx = 0, sepy = 0, seph = 0;
            unsigned int pattern = 0;
            if (std::sscanf(argument,"%f%c",
                            &N,&end)==2 && N>2) {
              N = cimg::round(N);
              const char
                *nargument = argument + cimg_snprintf(strint,sizeof(strint),"%u",
                                                      (unsigned int)N) + 1,
                *const eargument = argument + std::strlen(argument);
              CImg<float> coords0((unsigned int)N,2,1,1,0);
              CImg<bool> percents((unsigned int)N,2,1,1,0);
              for (unsigned int n = 0; n<(unsigned int)N; ++n) if (nargument<eargument) {
                  sepx = sepy = 0;
                  if (std::sscanf(nargument,"%255[0-9.eE%+-],%255[0-9.eE%+-]",
                                  argx,argy)==2 &&
                      (std::sscanf(argx,"%f%c",&x0,&end)==1 ||
                       (std::sscanf(argx,"%f%c%c",&x0,&sepx,&end)==2 && sepx=='%')) &&
                      (std::sscanf(argy,"%f%c",&y0,&end)==1 ||
                       (std::sscanf(argy,"%f%c%c",&y0,&sepy,&end)==2 && sepy=='%'))) {
                    coords0(n,0) = x0; percents(n,0) = (sepx=='%');
                    coords0(n,1) = y0; percents(n,1) = (sepy=='%');
                    nargument+=std::strlen(argx) + std::strlen(argy) + 2;
                  } else arg_error("polygon");
                } else arg_error("polygon");
              if (nargument<eargument &&
                  std::sscanf(nargument,"%4095[0-9.eE+-]",color)==1 &&
                  std::sscanf(color,"%f",&opacity)==1) {
                nargument+=std::strlen(color) + 1;
                *color = 0;
              }
              if (nargument<eargument &&
                  std::sscanf(nargument,"0%c%4095[0-9a-fA-F]",&seph,color)==2 && seph=='x' &&
                  std::sscanf(color,"%x%c",&pattern,&end)==1) {
                nargument+=std::strlen(color)+3;
                *color = 0;
              }
              const char *const _color = nargument<eargument?nargument:&(end=0);
              if (seph=='x')
                print(images,"Draw %g-vertices outlined polygon on image%s, with opacity %g, "
                      "pattern 0x%x and color (%s).",
                      N,
                      gmic_selection,
                      opacity,pattern,
                      *_color?_color:"default");
              else
                print(images,"Draw %g-vertices filled polygon on image%s, with opacity %g "
                      "and color (%s).",
                      N,
                      gmic_selection,
                      opacity,
                      *_color?_color:"default");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                CImg<int> coords(coords0);
                cimg_forX(coords,p) {
                  if (percents(p,0))
                    coords(p,0) = (int)cimg::round(coords0(p,0)*(img.width()-1)/100);
                  else coords(p,0) = (int)cimg::round(coords(p,0));
                  if (percents(p,1))
                    coords(p,1) = (int)cimg::round(coords0(p,1)*(img.height()-1)/100);
                  else coords(p,1) = (int)cimg::round(coords(p,1));
                }
                CImg<T> col(img.spectrum(),1,1,1,0);
                col.fill(_color,true);
                if (seph=='x') { gmic_apply(img,draw_polygon(coords,col.data(),opacity,pattern)); }
                else { gmic_apply(img,draw_polygon(coords,col.data(),opacity)); }
              }
            } else arg_error("polygon");
            is_released = false; ++position; continue;
          }

          // Draw plasma fractal.
          if (!std::strcmp("-plasma",command)) {
            gmic_substitute_args();
            float alpha = 1, beta = 1, scale = 8;
            if ((std::sscanf(argument,"%f%c",
                             &alpha,&end)==1 ||
                 std::sscanf(argument,"%f,%f%c",
                             &alpha,&beta,&end)==2 ||
                 std::sscanf(argument,"%f,%f,%f%c",
                             &alpha,&beta,&scale,&end)==3) &&
                scale>=0) {
              const unsigned int _scale = (unsigned int)cimg::round(scale);
              print(images,"Draw plasma fractal on image%s, with alpha %g, beta %g and scale %u.",
                    gmic_selection,
                    alpha,
                    beta,
                    _scale);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],draw_plasma(alpha,beta,_scale));
            } else arg_error("plasma");
            is_released = false; ++position; continue;
          }

          // Set 3d pose.
          if (!std::strcmp("-pose3d",item)) {
            gmic_substitute_args();
            float p3d[16] = { 0 };
            if (std::sscanf(argument,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f%c",
                            p3d,p3d+1,p3d+2,p3d+3,p3d+4,p3d+5,p3d+6,p3d+7,
                            p3d+8,p3d+9,p3d+10,p3d+11,p3d+12,p3d+13,p3d+14,p3d+15,
                            &end)==16) {
              print(images,"Set 3d pose matrix to [ %g,%g,%g,%g; %g,%g,%g,%g; %g,%g,%g,%g; "
                    "%g,%g,%g,%g ].",
                    p3d[0],p3d[1],p3d[2],p3d[3],
                    p3d[4],p3d[5],p3d[6],p3d[7],
                    p3d[8],p3d[9],p3d[10],p3d[11],
                    p3d[12],p3d[13],p3d[14],p3d[15]);
              pose3d.assign(p3d,4,4,1,1,false);
              ++position;
            } else {
              print(images,"Reset 3d pose matrix to default.");
              pose3d.assign();
            }
            continue;
          }

          // Convert 3d object primitives.
          if (!std::strcmp("-primitives3d",command)) {
            gmic_substitute_args();
            unsigned int mode = 0;
            if (std::sscanf(argument,"%u%c",
                            &mode,&end)==1 &&
                mode<=2) {
              print(images,"Convert primitives of 3d object%s to %s.",
                    gmic_selection,
                    mode==0?"points":mode==1?"segments":"no-textures");
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                CImg<T> &img = images[ind];
                if (!img.is_CImg3d(true,message))
                  error(images,"Command 'primitives3d': Invalid 3d object [%d], "
                        "in selected image%s (%s).",
                        ind,gmic_selection,message);
                CImgList<unsigned int> primitives;
                CImgList<float> colors, opacities;
                CImg<T> vertices;
                if (is_get_version) vertices.assign(img); else img.move_to(vertices);
                vertices.CImg3dtoobject3d(primitives,colors,opacities);
                const unsigned int psiz = primitives.size();
                CImg<unsigned int> P;
                CImg<float> C, O;
                for (unsigned int p = 0; p<psiz; ++p) {
                  primitives[p].move_to(P);
                  colors[p].move_to(C);
                  opacities[p].move_to(O);
                  switch (P.size()) {
                  case 1 : // Point.
                    P.move_to(primitives);
                    if (mode==2) {
                      if (C.size()==3) C.move_to(colors);
                      else C.get_vector_at(C.width()/2,C.height()/2).move_to(colors);
                      if (O.size()==1) O.move_to(opacities);
                      else O.get_vector_at(O.width()/2,O.height()/2).move_to(opacities);
                    } else { C.move_to(colors); O.move_to(opacities); }
                    break;
                  case 2 : // Colored segment.
                    if (mode) { P.move_to(primitives); C.move_to(colors); O.move_to(opacities); }
                    else {
                      CImg<unsigned int>::vector(P[0]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1]).move_to(primitives);
                      C.move_to(colors); O.move_to(opacities);
                    }
                    break;
                  case 3 : // Colored triangle.
                    if (mode==2) {
                      P.move_to(primitives); C.move_to(colors); O.move_to(opacities);
                    } else if (mode==1) {
                      CImg<unsigned int>::vector(P[0],P[1]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1],P[2]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[2],P[0]).move_to(primitives);
                      C.move_to(colors); O.move_to(opacities);
                    } else {
                      CImg<unsigned int>::vector(P[0]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[2]).move_to(primitives);
                      C.move_to(colors); O.move_to(opacities);
                    }
                    break;
                  case 4 : // Colored quadrangle.
                    if (mode==2) {
                      P.move_to(primitives); C.move_to(colors); O.move_to(opacities);
                    } else if (mode==1) {
                      CImg<unsigned int>::vector(P[0],P[1]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1],P[2]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[2],P[3]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[3],P[0]).move_to(primitives);
                      C.move_to(colors); O.move_to(opacities);
                    } else {
                      CImg<unsigned int>::vector(P[0]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[2]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[3]).move_to(primitives);
                      C.move_to(colors); O.move_to(opacities);
                    }
                    break;
                  case 5 : // Sphere.
                    if (mode==2) {
                      P.move_to(primitives); C.move_to(colors); O.move_to(opacities);
                    } else if (mode==1) {
                      CImg<unsigned int>::vector(P[0],P[1]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                    } else {
                      CImg<unsigned int>::vector(P[0]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1]).move_to(primitives);
                      colors.insert(C); opacities.insert(O);
                    }
                    break;
                  case 6 : // Textured segment.
                    if (mode==2) {
                      CImg<unsigned int>::vector(P[0],P[1]).move_to(primitives);
                      C.get_vector_at(P[2],P[3]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[2],P[3])).move_to(opacities);
                      else O.move_to(opacities);
                    } else if (mode==1) {
                      P.move_to(primitives); C.move_to(colors); O.move_to(opacities);
                    } else {
                      CImg<unsigned int>::vector(P[0]).move_to(primitives);
                      C.get_vector_at(P[2],P[3]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[2],P[3])).move_to(opacities);
                      else opacities.insert(O);
                      CImg<unsigned int>::vector(P[1]).move_to(primitives);
                      C.get_vector_at(P[4],P[5]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[4],P[5])).move_to(opacities);
                      else O.move_to(opacities);
                    }
                    break;
                  case 9 : // Textured triangle.
                    if (mode==2) {
                      CImg<unsigned int>::vector(P[0],P[1],P[2]).move_to(primitives);
                      C.get_vector_at(P[3],P[4]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[3],P[4])).move_to(opacities);
                      else O.move_to(opacities);
                    } else if (mode==1) {
                      CImg<unsigned int>::vector(P[0],P[1],P[3],P[4],P[5],P[6]).
                        move_to(primitives);
                      C.move_to(colors); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1],P[2],P[3],P[4],P[7],P[8]).
                        move_to(primitives);
                      colors.insert(colors.back(),~0U,true); opacities.insert(O);
                      CImg<unsigned int>::vector(P[2],P[0],P[7],P[8],P[1],P[3]).
                        move_to(primitives);
                      colors.insert(colors.back(),~0U,true); O.move_to(opacities);
                    } else {
                      CImg<unsigned int>::vector(P[0]).move_to(primitives);
                      C.get_vector_at(P[3],P[4]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[3],P[4])).move_to(opacities);
                      else opacities.insert(O);
                      CImg<unsigned int>::vector(P[1]).move_to(primitives);
                      C.get_vector_at(P[5],P[6]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[5],P[6])).move_to(opacities);
                      else opacities.insert(O);
                      CImg<unsigned int>::vector(P[2]).move_to(primitives);
                      C.get_vector_at(P[7],P[8]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[7],P[8])).move_to(opacities);
                      else O.move_to(opacities);
                    }
                    break;
                  case 12 : // Textured quadrangle.
                    if (mode==2) {
                      CImg<unsigned int>::vector(P[0],P[1],P[2],P[3]).move_to(primitives);
                      C.get_vector_at(P[4],P[5]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[4],P[5])).move_to(opacities);
                      else O.move_to(opacities);
                    } else if (mode==1) {
                      CImg<unsigned int>::vector(P[0],P[1],P[4],P[5],P[6],P[7]).
                        move_to(primitives);
                      C.move_to(colors); opacities.insert(O);
                      CImg<unsigned int>::vector(P[1],P[2],P[6],P[7],P[8],P[9]).
                        move_to(primitives);
                      colors.insert(colors.back(),~0U,true); opacities.insert(O);
                      CImg<unsigned int>::vector(P[2],P[3],P[8],P[9],P[10],P[11]).
                        move_to(primitives);
                      colors.insert(colors.back(),~0U,true); opacities.insert(O);
                      CImg<unsigned int>::vector(P[3],P[0],P[10],P[11],P[4],P[5]).
                        move_to(primitives);
                      colors.insert(colors.back(),~0U,true); O.move_to(opacities);
                    } else {
                      CImg<unsigned int>::vector(P[0]).move_to(primitives);
                      C.get_vector_at(P[4],P[5]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[4],P[5])).move_to(opacities);
                      else opacities.insert(O);
                      CImg<unsigned int>::vector(P[1]).move_to(primitives);
                      C.get_vector_at(P[6],P[7]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[6],P[7])).move_to(opacities);
                      else opacities.insert(O);
                      CImg<unsigned int>::vector(P[2]).move_to(primitives);
                      C.get_vector_at(P[8],P[9]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[8],P[9])).move_to(opacities);
                      else opacities.insert(O);
                      CImg<unsigned int>::vector(P[3]).move_to(primitives);
                      C.get_vector_at(P[10],P[11]).move_to(colors);
                      if (O.size()!=1) CImg<float>::vector(O(P[10],P[11])).move_to(opacities);
                      else O.move_to(opacities);
                    }
                    break;
                  default : // Other primitives.
                    P.move_to(primitives);
                    C.move_to(colors);
                    O.move_to(opacities);
                  }
                }
                if (psiz) {
                  primitives.remove(0,psiz-1);
                  colors.remove(0,psiz-1);
                  opacities.remove(0,psiz-1);
                }
                vertices.object3dtoCImg3d(primitives,colors,opacities);
                if (is_get_version) {
                  images_names.insert(images_names[selection[l]].get_mark().copymark());
                  vertices.move_to(images);
                } else {
                  images_names[selection[l]].mark();
                  vertices.move_to(images[selection[l]].assign());
                }
              }
            } else arg_error("primitives3d");
            is_released = false; ++position; continue;
          }

          // Display as a graph plot.
          if (!std::strcmp("-plot",command)) {
            gmic_substitute_args();
            double ymin = 0, ymax = 0, xmin = 0, xmax = 0;
            unsigned int plot_type = 1, vertex_type = 1;
            float resolution = 65536;
            char sep = 0;
            *formula = 0;
            if (((std::sscanf(argument,"'%1023[^']%c%c",
                              formula,&sep,&end)==2 && sep=='\'') ||
                 std::sscanf(argument,"'%1023[^']',%f%c",
                             formula,&resolution,&end)==2 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u%c",
                             formula,&resolution,&plot_type,&end)==3 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u,%u%c",
                             formula,&resolution,&plot_type,&vertex_type,&end)==4 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf%c",
                             formula,&resolution,&plot_type,&vertex_type,&xmin,&xmax,&end)==6 ||
                 std::sscanf(argument,"'%1023[^']',%f,%u,%u,%lf,%lf,%lf,%lf%c",
                             formula,&resolution,&plot_type,&vertex_type,
                             &xmin,&xmax,&ymin,&ymax,&end)==8) &&
                resolution>0 && plot_type<=3 && vertex_type<=7) {
              resolution = cimg::round(resolution);
              gmic_strreplace(formula);
              if (xmin==0 && xmax==0) { xmin = -4; xmax = 4; }
              if (!plot_type && !vertex_type) plot_type = 1;
              if (resolution<1) resolution = 65536;
              CImgList<double> tmp_img(1);
              CImg<double> &img = tmp_img[0];
              img.assign((unsigned int)resolution).eval(formula);
              const double dx = xmax - xmin;
              cimg_forX(img,X) img(X) = img.eval(0,xmin+X*dx/resolution);
              CImgList<char> tmp_name;
              cimg_snprintf(message,sizeof(message),"[Plot of '%s']",formula);
              CImg<char>::string(message).move_to(tmp_name);
              display_plots(tmp_img,tmp_name,CImg<unsigned int>::vector(0),
                            plot_type,vertex_type,xmin,xmax,ymin,ymax);
              ++position;
            } else {
              plot_type = 1; vertex_type = 0; ymin = ymax = xmin = xmax = 0;
              if ((std::sscanf(argument,"%u%c",
                               &plot_type,&end)==1 ||
                   std::sscanf(argument,"%u,%u%c",
                               &plot_type,&vertex_type,&end)==2 ||
                   std::sscanf(argument,"%u,%u,%lf,%lf%c",
                               &plot_type,&vertex_type,&xmin,&xmax,&end)==4 ||
                   std::sscanf(argument,"%u,%u,%lf,%lf,%lf,%lf%c",
                               &plot_type,&vertex_type,&xmin,&xmax,&ymin,&ymax,&end)==6) &&
                  plot_type<=3 && vertex_type<=7) ++position;
              if (!plot_type && !vertex_type) plot_type = 1;
              display_plots(images,images_names,selection,plot_type,vertex_type,
                            xmin,xmax,ymin,ymax);
            }
            is_released = true; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='p'.

        //----------------------------
        // Commands starting by '-q..'
        //----------------------------
        else if (command1=='q') {

#ifdef gmic_float

          // Draw quiver.
          if (!std::strcmp("-quiver",command)) {
            gmic_substitute_args();
            float sampling = 25, factor = -20, opacity = 1;
            unsigned int is_arrows = 1, pattern = ~0U;
            CImg<unsigned int> ind;
            char seph = 0;
            *color = 0;
            if ((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]]%c",
                             indices,&end)==1 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f%c",
                             indices,&sampling,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f%c",
                             indices,&sampling,&factor,&end)==3 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%u%c",
                             indices,&sampling,&factor,&is_arrows,&end)==4 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%u,%f%c",
                             indices,&sampling,&factor,&is_arrows,&opacity,&end)==5 ||
                 (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%u,%f,0%c%x%c",
                              indices,&sampling,&factor,&is_arrows,
                              &opacity,&seph,&pattern,&end)==7 && seph=='x') ||
                 (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%u,%f,%4095[0-9.eE,+-]%c",
                              indices,&sampling,&factor,&is_arrows,&opacity,color,&end)==6 &&
                  (pattern=~0U)) ||
                 (*color=0,std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%u,"
                                       "%f,0%c%x,%4095[0-9.eE,+-]%c",
                                       indices,&sampling,&factor,&is_arrows,
                                       &opacity,&seph,&pattern,color,&end)==8 &&
                  seph=='x')) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-quiver",true,
                                    false,CImg<char>::empty())).height()==1 &&
                sampling>0 && is_arrows<=1) {
              sampling = cimg::round(sampling);
              print(images,"Draw 2d vector field [%u] on image%s, with sampling %g, factor %g, "
                    "arrows %s, opacity %g, pattern 0x%x and color (%s).",
                    *ind,
                    gmic_selection,
                    sampling,
                    factor,
                    is_arrows?"enabled":"disabled",
                    opacity,pattern,
                    *color?color:"default");
              const CImg<T> flow = gmic_image_arg(*ind);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                gmic_apply(img,draw_quiver(flow,col.data(),opacity,(unsigned int)sampling,
                                           factor,(bool)is_arrows,pattern));
              }
            } else arg_error("quiver");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='q'.

        //----------------------------
        // Commands starting by '-r..'
        //----------------------------
        else if (command1=='r') {

          // Remove images.
          if (!std::strcmp("-remove",command)) {
            print(images,"Remove image%s",
                  gmic_selection);
            CImgList<T> _images;
            CImgList<char> _images_names;
            if (is_get_version) { _images.assign(images); _images_names.assign(images_names); }
            remove_images(images,images_names,selection,0,selection.height()-1);
            if (is_get_version) {
              _images.move_to(images,0);
              _images_names.move_to(images_names,0);
            }
            if (verbosity>=0 || is_debug) {
              std::fprintf(cimg::output()," (%u image%s left).",
                           images.size(),images.size()==1?"":"s");
              std::fflush(cimg::output());
            }
            is_released = false; continue;
          }

          // Repeat.
          if (!std::strcmp("-repeat",item)) {
            gmic_substitute_args();
            float number = 0;
            if (std::sscanf(argument,"%f%c",
                            &number,&end)==1) {
              const unsigned int nb = number>0?(unsigned int)cimg::round(number):0U;
              if (nb) {
                CImg<char>::string("*repeat").move_to(scope);
                if (verbosity>0 || is_debug)
                  print(images,"Start 'repeat..done' block (%u iteration%s).",
                        nb,nb>1?"s":"");
                CImg<unsigned int>::vector(position+1,nb,0).move_to(repeatdones);
              } else {
                if (verbosity>0 || is_debug)
                  print(images,"Skip 'repeat..done' block (0 iteration).",
                        nb);
                int nb_repeats = 0;
                for (nb_repeats = 1; nb_repeats && position<commands_line.size(); ++position) {
                  const char *it = commands_line[position].data();
                  if (!std::strcmp("-repeat",it)) ++nb_repeats;
                  else if (!std::strcmp("-done",it)) --nb_repeats;
                }
                if (nb_repeats && position>=commands_line.size())
                  error(images,"Command 'repeat': Missing associated 'done' command.");
                continue;
              }
            } else arg_error("repeat");
            ++position; continue;
          }

          // Resize.
          if (!std::strcmp("-resize",command)) {
            gmic_substitute_args();
            float valx = 100, valy = 100, valz = 100, valc = 100, cx = 0, cy = 0, cz = 0, cc = 0;
            char sep = 0, sepx = '%', sepy = '%', sepz = '%', sepc = '%';
            static char indicesy[256], indicesz[256], indicesc[256];
            CImg<unsigned int> ind, indx, indy, indz, indc;
            unsigned int boundary = 0;
            int interpolation = 1;
            *indices = *indicesy = *indicesz = *indicesc = *argx = *argy = *argz = *argc = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%d%c",
                             indices,&interpolation,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%d,%u%c",
                             indices,&interpolation,&boundary,&end)==3 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%d,%u,%f%c",
                             indices,&interpolation,&boundary,&cx,&end)==4 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%d,%u,%f,%f%c",
                             indices,&interpolation,&boundary,&cx,&cy,&end)==5 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%d,%u,%f,%f,%f%c",
                             indices,&interpolation,&boundary,&cx,&cy,&cz,&end)==6 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%d,%u,%f,%f,%f,%f%c",
                             indices,&interpolation,&boundary,&cx,&cy,&cz,&cc,&end)==7) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-resize",true,
                                    false,CImg<char>::empty())).height()==1 &&
                interpolation>=-1 && interpolation<=6 && boundary<=2 &&
                cx>=0 && cx<=1 && cy>=0 && cy<=1 && cz>=0 && cz<=1 && cc>=0 && cc<=1) {
              const int
                nvalx = images[*ind].width(),
                nvaly = images[*ind].height(),
                nvalz = images[*ind].depth(),
                nvalc = images[*ind].spectrum();
              print(images,"Resize image%s to %dx%dx%dx%d, with %s interpolation, %s boundary and "
                    "alignment (%g,%g,%g,%g).",
                    gmic_selection,
                    nvalx,nvaly,nvalz,nvalc,
                    interpolation<=0?"no":interpolation==1?"nearest-neighbor":
                    interpolation==2?"moving average":interpolation==3?"linear":
                    interpolation==4?"grid":interpolation==5?"bicubic":"lanczos",
                    boundary<=0?"dirichlet":boundary==1?"neumann":"cyclic",
                    cx,cy,cz,cc);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],resize(nvalx,nvaly,nvalz,nvalc,interpolation,
                                                       boundary,cx,cy,cz,cc));
              ++position;
            } else if ((cx=cy=cz=cc=0, interpolation=1, boundary=0, true) &&
                       (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-]%c",
                                    argx,&end)==1 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                                    argx,argy,&end)==2 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-]%c",
                                    argx,argy,argz,&end)==3 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                                    argx,argy,argz,argc,&end)==4 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],%d%c",
                                    argx,argy,argz,argc,&interpolation,&end)==5 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],%d,%u%c",
                                    argx,argy,argz,argc,&interpolation,&boundary,&end)==6 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],%d,%u,%f%c",
                                    argx,argy,argz,argc,&interpolation,&boundary,&cx,&end)==7 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],%d,%u,%f,"
                                    "%f%c",
                                    argx,argy,argz,argc,&interpolation,&boundary,&cx,&cy,&end)==8||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],%d,%u,%f,"
                                    "%f,%f%c",
                                    argx,argy,argz,argc,&interpolation,&boundary,
                                    &cx,&cy,&cz,&end)==9 ||
                        std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                                    "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],%d,%u,%f,"
                                    "%f,%f,%f%c",
                                    argx,argy,argz,argc,&interpolation,&boundary,
                                    &cx,&cy,&cz,&cc,&end)==10) &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sepx,&end)==2 &&
                         sepx==']' &&
                         (indx=selection2cimg(indices,images.size(),images_names,"-resize",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        (sepx=0,std::sscanf(argx,"%f%c",&valx,&sepx)==1 && valx>=1) ||
                        (std::sscanf(argx,"%f%c%c",&valx,&sepx,&end)==2 && sepx=='%')) &&
                       (!*argy ||
                        (std::sscanf(argy,"[%255[a-zA-Z0-9_.%+-]%c%c",indicesy,&sepy,&end)==2 &&
                         sepy==']' &&
                         (indy=selection2cimg(indicesy,images.size(),images_names,"-resize",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        (sepy=0,std::sscanf(argy,"%f%c",&valy,&sepy)==1 && valy>=1) ||
                        (std::sscanf(argy,"%f%c%c",&valy,&sepy,&end)==2 && sepy=='%')) &&
                       (!*argz ||
                        (std::sscanf(argz,"[%255[a-zA-Z0-9_.%+-]%c%c",indicesz,&sepz,&end)==2 &&
                         sepz==']' &&
                         (indz=selection2cimg(indicesz,images.size(),images_names,"-resize",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        (sepz=0,std::sscanf(argz,"%f%c",&valz,&sepz)==1 && valz>=1) ||
                        (std::sscanf(argz,"%f%c%c",&valz,&sepz,&end)==2 && sepz=='%')) &&
                       (!*argc ||
                        (std::sscanf(argc,"[%255[a-zA-Z0-9_.%+-]%c%c",indicesc,&sepc,&end)==2 &&
                         sepc==']' &&
                         (indc=selection2cimg(indicesc,images.size(),images_names,"-resize",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        (sepc=0,std::sscanf(argc,"%f%c",&valc,&sepc)==1 && valc>=1) ||
                        (std::sscanf(argc,"%f%c%c",&valc,&sepc,&end)==2 && sepc=='%')) &&
                     valx>0 && valy>0 && valz>0 && valc>0 &&
                       interpolation>=-1 && interpolation<=6 && boundary<=2 &&
                       cx>=0 && cx<=1 && cy>=0 && cy<=1 && cz>=0 && cz<=1 && cc>=0 && cc<=1) {
              if (indx) { valx = (float)images[*indx].width(); sepx = 0; }
              if (indy) { valy = (float)images[*indy].height(); sepy = 0; }
              if (indz) { valz = (float)images[*indz].depth(); sepz = 0; }
              if (indc) { valc = (float)images[*indc].spectrum(); sepc = 0; }
              print(images,
                    "Resize image%s to %g%s%g%s%g%s%g%s, with %s interpolation, %s boundary "
                    "and alignment (%g,%g,%g,%g).",
                    gmic_selection,
                    valx,sepx=='%'?"%x":"x",
                    valy,sepy=='%'?"%x":"x",
                    valz,sepz=='%'?"%x":"x",
                    valc,sepc=='%'?"% ":"",
                    interpolation<=0?"no":interpolation==1?"nearest neighbor":
                    interpolation==2?"moving average":interpolation==3?"linear":
                    interpolation==4?"grid":interpolation==5?"bicubic":"lanczos",
                    boundary<=0?"dirichlet":boundary==1?"neumann":"cyclic",
                    cx,cy,cz,cc);
              cimg_forY(selection,l) {
                CImg<T>& img = images[selection[l]];
                const int
                  _nvalx = (int)cimg::round(sepx=='%'?valx*img.width()/100:valx),
                  _nvaly = (int)cimg::round(sepy=='%'?valy*img.height()/100:valy),
                  _nvalz = (int)cimg::round(sepz=='%'?valz*img.depth()/100:valz),
                  _nvalc = (int)cimg::round(sepc=='%'?valc*img.spectrum()/100:valc),
                  nvalx = _nvalx?_nvalx:1,
                  nvaly = _nvaly?_nvaly:1,
                  nvalz = _nvalz?_nvalz:1,
                  nvalc = _nvalc?_nvalc:1;
                gmic_apply(img,resize(nvalx,nvaly,nvalz,nvalc,interpolation,boundary,cx,cy,cz,cc));
              }
              ++position;
            } else {
#if cimg_display==0
              print(images,"Resize image%s in interactive mode (skipped, no display support).",
                    gmic_selection);
#else // #if cimg_display==0
              bool is_available_display = false;
              try {
                is_available_display = (bool)CImgDisplay::screen_width();
              } catch (CImgDisplayException&) {
                print(images,"Resize image%s in interactive mode (skipped, no display available).",
                      gmic_selection);
              }
              if (is_available_display) {
                print(images,"Resize image%s in interactive mode.",
                      gmic_selection);
                CImgDisplay _disp, &disp = instant_window[0]?instant_window[0]:_disp;
                cimg_forY(selection,l) {
                  CImg<T>& img = images[selection[l]];
                  if (img) {
                    if (disp) disp.resize(cimg_fitscreen(img.width(),img.height(),1),false);
                    else disp.assign(cimg_fitscreen(img.width(),img.height(),1),0,1);
                    disp.set_title("%s: resize",gmic_basename(images_names[selection[l]].data()));
                    img.get_select(disp,0);
                    print(images,
                          "Resize image [%d] to %dx%d, with nearest-neighbor interpolation.",
                          selection[l],
                          disp.width(),
                          disp.height());
                    gmic_apply(img,resize(disp));
                  } else { gmic_apply(img,replace(img)); }
                }
              }
#endif // #if cimg_display==0
            }
            is_released = false; continue;
          }

          // Reverse positions.
          if (!std::strcmp("-reverse",command)) {
            print(images,"Reverse positions of image%s.",
                  gmic_selection);
            CImgList<T> _images, nimages(selection.height());
            CImgList<char> _images_names, nimages_names(selection.height());
            if (is_get_version) { _images.assign(images); _images_names.assign(images_names); }
            cimg_forY(selection,l) {
              nimages[l].swap(images[selection[l]]);
              nimages_names[l].swap(images_names[selection[l]]);
            }
            nimages.reverse(); nimages_names.reverse();
            cimg_forY(selection,l) {
              nimages[l].swap(images[selection[l]]);
              nimages_names[l].swap(images_names[selection[l]]);
            }
            if (is_get_version) {
              _images.move_to(images,0);
              _images_names.move_to(images_names,0);
            }
            is_released = false; continue;
          }

          // Return.
          if (!std::strcmp("-return",item)) {
            if (verbosity>0 || is_debug) print(images,"Return.");
            position = commands_line.size();
            while (scope && scope.back()[0]=='*') {
              const char c = scope.back()[1];
              if (c=='d') dowhiles.remove();
              else if (c=='r') repeatdones.remove();
              else if (c=='l' || c=='>' || c=='s') break;
              scope.remove();
            }
            is_return = true;
            break;
          }

          // Keep rows.
          if (!std::strcmp("-rows",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind0, ind1;
            float value0 = 0, value1 = 0;
            char sep0 = 0, sep1 = 0;
            *argx = *argy = 0;
            if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-]%c",
                            argx,&end)==1 &&
                ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c]",indices,&sep0,&end)==2 &&
                  sep0==']' &&
                  (ind0=selection2cimg(indices,images.size(),images_names,"-rows",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%'))) {
              if (ind0) { value0 = images[*ind0].height() - 1.0f; sep0 = 0; }
              print(images,"Keep rows %g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.height()-1)/100:value0);
                gmic_apply(img,row(nvalue0));
              }
            } else if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                                   argx,argy,&end)==2 &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind0=selection2cimg(indices,images.size(),images_names,"-rows",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                        (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%')) &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",formula,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind1=selection2cimg(formula,images.size(),images_names,"-rows",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argy,"%f%c",&value1,&end)==1 ||
                        (std::sscanf(argy,"%f%c%c",&value1,&sep1,&end)==2 && sep1=='%'))) {
              if (ind0) { value0 = images[*ind0].height() - 1.0f; sep0 = 0; }
              if (ind1) { value1 = images[*ind1].height() - 1.0f; sep1 = 0; }
              print(images,"Keep rows %g%s..%g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.height()-1)/100:value0),
                  nvalue1 = (int)cimg::round(sep1=='%'?value1*(img.height()-1)/100:value1);
                gmic_apply(img,rows(nvalue0,nvalue1));
              }
            } else arg_error("rows");
            is_released = false; ++position; continue;
          }

          // Rotate.
          if (!std::strcmp("-rotate",command)) {
            gmic_substitute_args();
            float angle = 0, zoom = 1, cx = 0, cy = 0;
            unsigned int boundary = 0, interpolation = 1;
            char sepx = 0, sepy = 0;
            *argx = *argy = 0;
            if ((std::sscanf(argument,"%f%c",
                             &angle,&end)==1 ||
                 std::sscanf(argument,"%f,%u%c",
                             &angle,&boundary,&end)==2 ||
                 std::sscanf(argument,"%f,%u,%u%c",
                             &angle,&boundary,&interpolation,&end)==3 ||
                 std::sscanf(argument,"%f,%u,%u,%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             &angle,&boundary,&interpolation,argx,argy,&end)==5 ||
                 std::sscanf(argument,"%f,%u,%u,%255[0-9.eE%+-],%255[0-9.eE%+-],%f%c",
                             &angle,&boundary,&interpolation,argx,argy,&zoom,&end)==6) &&
                (!*argx ||
                 std::sscanf(argx,"%f%c",&cx,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&cx,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&cy,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&cy,&sepy,&end)==2 && sepy=='%')) &&
                boundary<=2 && interpolation<=2) {
              if (*argx) {
                print(images,"Rotate image%s of %g°, %s boundary, %s interpolation, "
                      "with center at (%g%s,%g%s).",
                      gmic_selection,angle,
                      boundary==0?"dirichlet":boundary==1?"neumann":"cyclic",
                      interpolation==0?"nearest-neighbor":interpolation==1?"linear":"bicubic",
                      cx,sepx=='%'?"%":"",cy,sepy=='%'?"%":"");
                cimg_forY(selection,l) {
                  CImg<T> &img = images[selection[l]];
                  const float
                    ncx = sepx=='%'?cx*(img.width()-1)/100:cx,
                    ncy = sepy=='%'?cy*(img.height()-1)/100:cy;
                  gmic_apply(img,rotate(angle,ncx,ncy,zoom,boundary,interpolation));
                }
              } else {
                print(images,"Rotate image%s of %g°, %s boundary and %s interpolation.",
                      gmic_selection,angle,
                      boundary==0?"dirichlet":boundary==1?"neumann":"cyclic",
                      interpolation==0?"nearest-neighbor":interpolation==1?"linear":"bicubic");
                cimg_forY(selection,l)
                  gmic_apply(images[selection[l]],rotate(angle,boundary,interpolation));
              }
            } else arg_error("rotate");
            is_released = false; ++position; continue;
          }

          // Resize2x.
          gmic_simple_item("-resize2x",resize_doubleXY,
                           "Double xy-dimensions of image%s, using Scale2x algorithm.");

          // Resize3x.
          gmic_simple_item("-resize3x",resize_tripleXY,
                           "Triple xy-dimensions of image%s, using Scale3x algorithm.");

#ifdef gmic_float

          // Round.
          if (!std::strcmp("-round",command)) {
            gmic_substitute_args();
            double rounding_value = 1;
            int rounding_type = 0;
            if ((std::sscanf(argument,"%lf%c",
                             &rounding_value,&end)==1 ||
                 std::sscanf(argument,"%lf,%d%c",
                             &rounding_value,&rounding_type,&end)==2) &&
                rounding_value>=0 && rounding_type>=-1 && rounding_type<=1) ++position;
            else { rounding_value = 1; rounding_type = 0; }
            print(images,"Round values of image%s by %g and %s rounding.",
                  gmic_selection,
                  rounding_value,
                  rounding_type<0?"backward":rounding_type>0?"forward":"nearest");
            cimg_forY(selection,l)
              gmic_apply(images[selection[l]],round(rounding_value,rounding_type));
            is_released = false; continue;
          }

          // Fill with random values.
          if (!std::strcmp("-rand",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind0, ind1;
            double value0 = 0, value1 = 0;
            char sep0 = 0, sep1 = 0;
            *argx = *argy = 0;
            if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                            argx,argy,&end)==2 &&
                ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                  sep0==']' &&
                  (ind0=selection2cimg(indices,images.size(),images_names,"-rand",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 (std::sscanf(argx,"%lf%c%c",&value0,&sep0,&end)==2 && sep0=='%') ||
                 std::sscanf(argx,"%lf%c",&value0,&end)==1) &&
                ((std::sscanf(argy,"[%255[a-zA-Z0-9_.%+-]%c%c",formula,&sep1,&end)==2 &&
                  sep1==']' &&
                  (ind1=selection2cimg(formula,images.size(),images_names,"-rand",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 (std::sscanf(argy,"%lf%c%c",&value1,&sep1,&end)==2 && sep1=='%') ||
                 std::sscanf(argy,"%lf%c",&value1,&end)==1)) {
              if (ind0) { value0 = images[*ind0].min(); sep0 = 0; }
              if (ind1) { value1 = images[*ind1].max(); sep1 = 0; }
              print(images,"Fill image%s with random values, in range [%g%s,%g%s].",
                    gmic_selection,
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                double vmin = 0, vmax = 0, nvalue0 = value0, nvalue1 = value1;
                if (sep0=='%' || sep1=='%') {
                  if (img) vmax = (double)img.max_min(vmin);
                  if (sep0=='%') nvalue0 = vmin + (vmax-vmin)*value0/100;
                  if (sep1=='%') nvalue1 = vmin + (vmax-vmin)*value1/100;
                }
                gmic_apply(img,rand((T)nvalue0,(T)nvalue1));
              }
            } else if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                       sep0==']' &&
                       (ind0=selection2cimg(indices,images.size(),images_names,"-rand",true,
                                            false,CImg<char>::empty())).height()==1) {
              if (images[*ind0]) value1 = (double)images[*ind0].max_min(value0);
              print(images,"Fill image%s with random values, in range [%g,%g] from image [%d].",
                    gmic_selection,
                    value0,
                    value1,
                    *ind0);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],rand((T)value0,(T)value1));
            } else arg_error("rand");
            is_released = false; ++position; continue;
          }

          // Rotate 3d object.
          if (!std::strcmp("-rotate3d",command)) {
            gmic_substitute_args();
            float u = 0, v = 0, w = 1, angle = 0;
            if (std::sscanf(argument,"%f,%f,%f,%f%c",
                            &u,&v,&w,&angle,&end)==4) {
              print(images,"Rotate 3d object%s around axis (%g,%g,%g), with angle %g°.",
                    gmic_selection,
                    u,v,w,
                    angle);
              const CImg<float> rot = CImg<float>::rotation_matrix(u,v,w,
                                                                   (float)(angle*cimg::PI/180));
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (!images[ind].is_CImg3d(false,message))
                  error(images,"Command 'rotate3d': Invalid 3d object [%d], "
                        "in selected image%s (%s).",
                        ind,gmic_selection,message);
                gmic_apply(images[ind],rotate_CImg3d(rot));
              }
            } else arg_error("rotate3d");
            is_released = false; ++position; continue;
          }

          // RGB to other color base.
          gmic_simple_item("-rgb2hsi",RGBtoHSI,"Convert image%s from RGB to HSI color bases.");
          gmic_simple_item("-rgb2hsl",RGBtoHSL,"Convert image%s from RGB to HSL color bases.");
          gmic_simple_item("-rgb2hsv",RGBtoHSV,"Convert image%s from RGB to HSV color bases.");
          gmic_simple_item("-rgb2lab",RGBtoLab,"Convert image%s from RGB to Lab color bases.");
          gmic_simple_item("-rgb2srgb",RGBtosRGB,"Convert image%s from RGB to sRGB color bases.");

          // Bitwise left rotation.
          gmic_arithmetic_item("-rol",
                               gmic_rol,
                               "Compute bitwise left rotation of image%s by %g%s",
                               gmic_selection,(int)value,ssep,T,
                               rol,
                               "Compute bitwise left rotation of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute bitwise left rotation of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential bitwise left rotation of image%s");

          // Bitwise right rotation.
          gmic_arithmetic_item("-ror",
                               gmic_ror,
                               "Compute bitwise right rotation of image%s by %g%s",
                               gmic_selection,value,ssep,T,
                               ror,
                               "Compute bitwise right rotation of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute bitwise left rotation of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential bitwise left rotation of image%s");

          // Reverse 3d object orientation.
          if (!std::strcmp("-reverse3d",command)) {
            print(images,"Reverse orientation of 3d object%s.",
                  gmic_selection);
            cimg_forY(selection,l) {
              const unsigned int ind = selection[l];
              CImg<T> &img = images[ind];
              if (!img.is_CImg3d(true,message))
                error(images,"Command 'reverse3d': Invalid 3d object [%d], "
                      "in selected image%s (%s).",
                      ind,gmic_selection,message);
              CImgList<unsigned int> primitives;
              CImgList<float> colors, opacities;
              CImg<T> vertices;
              if (is_get_version) vertices.assign(img); else img.move_to(vertices);
              vertices.CImg3dtoobject3d(primitives,colors,opacities);
              primitives.reverse_object3d();
              vertices.object3dtoCImg3d(primitives,colors,opacities);
              if (is_get_version) {
                images_names.insert(images_names[selection[l]].get_mark().copymark());
                vertices.move_to(images);
              } else {
                images_names[selection[l]].mark();
                vertices.move_to(images[selection[l]].assign());
              }
            }
            is_released = false; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='r'.

        //----------------------------
        // Commands starting by '-s..'
        //----------------------------
        else if (command1=='s') {

          // Set status
          if (!std::strcmp("-status",item)) {
            gmic_substitute_args();
            print(images,"Set status to '%s'.",argument_text);
            CImg<char>::string(argument).move_to(status);
            ++position; continue;
          }

          // Skip argument.
          if (!std::strcmp("-skip",item)) {
            gmic_substitute_args();
            if (verbosity>0 || is_debug)
              print(images,"Skip argument '%s'.",
                    argument_text);
            ++position;
            continue;
          }

          // Set pixel value.
          if (!std::strcmp("-set",command)) {
            gmic_substitute_args();
            char sepx = 0, sepy = 0, sepz = 0, sepc = 0;
            float x = 0, y = 0, z = 0, c = 0;
            double value = 0;
            *argx = *argy = *argz = *argc = 0;
            if ((std::sscanf(argument,"%lf%c",
                             &value,&end)==1 ||
                 std::sscanf(argument,"%lf,%255[0-9.eE%+-]%c",
                             &value,argx,&end)==2 ||
                 std::sscanf(argument,"%lf,%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             &value,argx,argy,&end)==3 ||
                 std::sscanf(argument,"%lf,%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             &value,argx,argy,argz,&end)==4 ||
                 std::sscanf(argument,"%lf,%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-]%c",
                             &value,argx,argy,argz,argc,&end)==5) &&
                (!*argx ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%') ||
                 std::sscanf(argx,"%f%c",&x,&end)==1) &&
                (!*argy ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%') ||
                 std::sscanf(argy,"%f%c",&y,&end)==1) &&
                (!*argz ||
                 (std::sscanf(argz,"%f%c%c",&z,&sepz,&end)==2 && sepz=='%') ||
                 std::sscanf(argz,"%f%c",&z,&end)==1) &&
                (!*argc ||
                 (std::sscanf(argc,"%f%c%c",&c,&sepc,&end)==2 && sepc=='%') ||
                 std::sscanf(argc,"%f%c",&c,&end)==1)) {
              print(images,"Set value %g in image%s, at coordinates (%g%s,%g%s,%g%s,%g%s).",
                    value,
                    gmic_selection,
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    z,sepz=='%'?"%":"",
                    c,sepc=='%'?"%":"");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y),
                  nz = (int)cimg::round(sepz=='%'?z*(img.depth()-1)/100:z),
                  nc = (int)cimg::round(sepc=='%'?c*(img.spectrum()-1)/100:c);
                gmic_apply(images[selection[l]],gmic_set(value,nx,ny,nz,nc));
              }
            } else arg_error("set");
            is_released = false; ++position; continue;
          }

          // Split.
          if (!std::strcmp("-split",command)) {
            gmic_substitute_args();
            const char *axis_arg = 0;
            char keep_values = '+';
            CImgList<char> axes;
            float nb = 0;
            for (axis_arg = argument; *axis_arg && *axis_arg!=','; ++axis_arg) {
              const char _s = *axis_arg;
              if (_s!='x' && _s!='y' && _s!='z' && _s!='c') { axis_arg = 0; break; }
              CImg<char>::vector(_s).move_to(axes);
            }
            if (axis_arg && *axis_arg==',') {
              if (std::sscanf(++axis_arg,"%f%c",&nb,&end)!=1) axis_arg = 0;
              else nb = cimg::round(nb);
            }
            if (axes && axis_arg) {
              const CImg<char> _axes = (axes,CImg<char>::vector(0))>'x';
              axes.remove();
              if (nb>0)
                print(images,"Split image%s along the '%s'-ax%cs, into %g parts.",
                      gmic_selection,
                      _axes.data(),
                      axes.size()>1?'e':'i',
                      nb);
              else if (nb<0)
                print(images,"Split image%s along the '%s'-ax%cs, into blocs of %g pixels.",
                      gmic_selection,
                      _axes.data(),
                      axes.size()>1?'e':'i',
                      -nb);
              else
                print(images,"Split image%s along the '%s'-ax%cs.",
                      gmic_selection,
                      _axes.data(),
                      axes.size()>1?'e':'i');
              unsigned int off = 0;
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l] + off;
                const CImg<T>& img = images[ind];
                if (img) {
                  CImg<char> name = images_names[ind].get_mark();
                  CImgList<T> split(img,true);
                  cimglist_for(axes,i) {
                    const unsigned int N = split.size();
                    for (unsigned int l = 0; l<N; ++l) {
                      split[0].get_split(axes(i,0),(int)nb).move_to(split,~0U);
                      split.remove(0);
                    }
                  }
                  if (is_get_version) {
                    images_names.insert(split.size(),name.copymark());
                    split.move_to(images,~0U);
                  } else {
                    images.remove(ind);
                    images_names.remove(ind);
                    off+=split.size() - 1;
                    images_names.insert(split.size(),name.get_copymark(),ind);
                    name.move_to(images_names[ind]);
                    split.move_to(images,ind);
                  }
                }
              }
            } else if ((std::sscanf(argument,"%c,%c",
                                    &keep_values,&end)==2) &&
                       (keep_values=='+' || keep_values=='-')) {
              print(images,"Split image%s in %s mode, according to value sequence '%s'.",
                    gmic_selection,
                    keep_values=='-'?"discard":"keep",
                    argument_text+2);
              unsigned int off = 0, nb_values = 1;
              for (const char *s = argument+2; *s; ++s) if (*s==',') ++nb_values;
              const CImg<T> values(nb_values,1,1,1,argument+2,true);
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l] + off;
                const CImg<T>& img = images[ind];
                if (img) {
                  CImg<char> name = images_names[ind].get_mark();
                  CImgList<T> split = images[ind].get_split(values,keep_values=='+',false);
                  if (is_get_version) {
                    if (split) {
                      images_names.insert(split.size(),name.copymark());
                      split.move_to(images,~0U);
                    }
                  } else {
                    images.remove(ind);
                    images_names.remove(ind);
                    if (split) {
                      off+=split.size() - 1;
                      images_names.insert(split.size(),name.get_copymark(),ind);
                      name.move_to(images_names[ind]);
                      split.move_to(images,ind);
                    }
                  }
                }
              }
            } else arg_error("split");
            is_released = false; ++position; continue;
          }

          // Shared input.
          if (!std::strcmp("-shared",command)) {
            gmic_substitute_args();
            static char st0[256], st1[256], st2[256], st3[256], st4[256];
            char sep0 = 0, sep1 = 0, sep2 = 0, sep3 = 0, sep4 = 0;
            float a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0;
            *st0 = *st1 = *st2 = *st3 = *st4 = 0;
            if (std::sscanf(argument,
                            "%255[0-9.eE%+],%255[0-9.eE%+],%255[0-9.eE%+],%255[0-9.eE%+],"
                            "%255[0-9.eE%+]%c",
                            st0,st1,st2,st3,st4,&end)==5 &&
                (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                 (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                 (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%')) &&
                (std::sscanf(st2,"%f%c",&a2,&end)==1 ||
                 (std::sscanf(st2,"%f%c%c",&a2,&sep2,&end)==2 && sep2=='%')) &&
                (std::sscanf(st3,"%f%c",&a3,&end)==1 ||
                 (std::sscanf(st3,"%f%c%c",&a3,&sep3,&end)==2 && sep3=='%')) &&
                (std::sscanf(st4,"%f%c",&a4,&end)==1 ||
                 (std::sscanf(st4,"%f%c%c",&a4,&sep4,&end)==2 && sep4=='%'))) {
              print(images,
                    "Insert shared buffer%s from points (%g%s->%g%s,%g%s,%g%s,%g%s) of image%s.",
                    selection.height()>1?"s":"",
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    a2,sep2=='%'?"%":"",
                    a3,sep3=='%'?"%":"",
                    a4,sep4=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const unsigned int
                  s0 = (unsigned int)cimg::round(sep0=='%'?a0*(img.width()-1)/100:a0),
                  s1 = (unsigned int)cimg::round(sep1=='%'?a1*(img.width()-1)/100:a1),
                  y =  (unsigned int)cimg::round(sep2=='%'?a2*(img.height()-1)/100:a2),
                  z =  (unsigned int)cimg::round(sep3=='%'?a3*(img.depth()-1)/100:a3),
                  c =  (unsigned int)cimg::round(sep4=='%'?a4*(img.spectrum()-1)/100:a4);
                images.insert(img.get_shared_points(s0,s1,y,z,c),~0U,true);
                images_names.insert(images_names[selection[l]].get_copymark());
              }
              ++position;
            } else if (std::sscanf(argument,
                                   "%255[0-9.eE%+],%255[0-9.eE%+],%255[0-9.eE%+],"
                                   "%255[0-9.eE%+],%c",
                                   st0,st1,st2,st3,&end)==4 &&
                       (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                        (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                       (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                        (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%')) &&
                       (std::sscanf(st2,"%f%c",&a2,&end)==1 ||
                        (std::sscanf(st2,"%f%c%c",&a2,&sep2,&end)==2 && sep2=='%')) &&
                       (std::sscanf(st3,"%f%c",&a3,&end)==1 ||
                        (std::sscanf(st3,"%f%c%c",&a3,&sep3,&end)==2 && sep3=='%'))) {
              print(images,"Insert shared buffer%s from lines (%g%s->%g%s,%g%s,%g%s) of image%s.",
                    selection.height()>1?"s":"",
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    a2,sep2=='%'?"%":"",
                    a3,sep3=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const unsigned int
                  s0 = (unsigned int)cimg::round(sep0=='%'?a0*(img.height()-1)/100:a0),
                  s1 = (unsigned int)cimg::round(sep1=='%'?a1*(img.height()-1)/100:a1),
                  z =  (unsigned int)cimg::round(sep2=='%'?a2*(img.depth()-1)/100:a2),
                  c =  (unsigned int)cimg::round(sep3=='%'?a3*(img.spectrum()-1)/100:a3);
                images.insert(img.get_shared_rows(s0,s1,z,c),~0U,true);
                images_names.insert(images_names[selection[l]].get_copymark());
              }
              ++position;
            } else if (std::sscanf(argument,"%255[0-9.eE%+],%255[0-9.eE%+],%255[0-9.eE%+]%c",
                                   st0,st1,st2,&end)==3 &&
                       (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                        (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                       (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                        (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%')) &&
                       (std::sscanf(st2,"%f%c",&a2,&end)==1 ||
                        (std::sscanf(st2,"%f%c%c",&a2,&sep2,&end)==2 && sep2=='%'))) {
              print(images,"Insert shared buffer%s from planes (%g%s->%g%s,%g%s) of image%s.",
                    selection.height()>1?"s":"",
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    a2,sep2=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const unsigned int
                  s0 = (unsigned int)cimg::round(sep0=='%'?a0*(img.depth()-1)/100:a0),
                  s1 = (unsigned int)cimg::round(sep1=='%'?a1*(img.depth()-1)/100:a1),
                  c =  (unsigned int)cimg::round(sep2=='%'?a2*(img.spectrum()-1)/100:a2);
                images.insert(img.get_shared_slices(s0,s1,c),~0U,true);
                images_names.insert(images_names[selection[l]].get_copymark());
              }
              ++position;
            } else if (std::sscanf(argument,"%255[0-9.eE%+],%255[0-9.eE%+]%c",
                                   st0,st1,&end)==2 &&
                       (std::sscanf(st0,"%f%c",&a0,&end)==1 ||
                        (std::sscanf(st0,"%f%c%c",&a0,&sep0,&end)==2 && sep0=='%')) &&
                       (std::sscanf(st1,"%f%c",&a1,&end)==1 ||
                        (std::sscanf(st1,"%f%c%c",&a1,&sep1,&end)==2 && sep1=='%'))) {
              print(images,"Insert shared buffer%s from channels (%g%s->%g%s) of image%s.",
                    selection.height()>1?"s":"",
                    a0,sep0=='%'?"%":"",
                    a1,sep1=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const unsigned int
                  s0 = (unsigned int)cimg::round(sep0=='%'?a0*(img.spectrum()-1)/100:a0),
                  s1 = (unsigned int)cimg::round(sep1=='%'?a1*(img.spectrum()-1)/100:a1);
                images.insert(img.get_shared_channels(s0,s1),~0U,true);
                images_names.insert(images_names[selection[l]].get_copymark());
              }
              ++position;
            } else {
              print(images,"Insert shared buffer%s from image%s.",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                images.insert(img,~0U,true);
                images_names.insert(images_names[selection[l]].get_copymark());
              }
            }
            is_released = false; continue;
          }

          // Shift.
          if (!std::strcmp("-shift",command)) {
            gmic_substitute_args();
            char sepx = 0, sepy = 0, sepz = 0, sepc = 0;
            float dx = 0, dy = 0, dz = 0, dc = 0;
            unsigned int boundary = 0;
            *argx = *argy = *argz = *argc = 0;
            if ((std::sscanf(argument,"%255[0-9.eE%+-]%c",
                             argx,&end)==1 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,&end)==2 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,argz,&end)==3 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-]%c",
                             argx,argy,argz,argc,&end)==4 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%u%c",
                             argx,argy,argz,argc,&boundary,&end)==5) &&
                (std::sscanf(argx,"%f%c",&dx,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&dx,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&dy,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&dy,&sepy,&end)==2 && sepy=='%')) &&
                (!*argz ||
                 std::sscanf(argz,"%f%c",&dz,&end)==1 ||
                 (std::sscanf(argz,"%f%c%c",&dz,&sepz,&end)==2 && sepz=='%')) &&
                (!*argc ||
                 std::sscanf(argc,"%f%c",&dc,&end)==1 ||
                 (std::sscanf(argc,"%f%c%c",&dc,&sepc,&end)==2 && sepc=='%')) &&
                boundary<=2) {
              print(images,
                    "Shift image%s by displacement vector (%g%s,%g%s,%g%s,%g%s) and %s boundary.",
                    gmic_selection,
                    dx,sepx=='%'?"%":"",
                    dy,sepy=='%'?"%":"",
                    dz,sepz=='%'?"%":"",
                    dc,sepc=='%'?"%":"",
                    boundary==0?"dirichlet":boundary==1?"neumann":"cyclic");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  ndx = (int)cimg::round(sepx=='%'?dx*img.width()/100:dx),
                  ndy = (int)cimg::round(sepy=='%'?dy*img.height()/100:dy),
                  ndz = (int)cimg::round(sepz=='%'?dz*img.depth()/100:dz),
                  ndc = (int)cimg::round(sepc=='%'?dc*img.spectrum()/100:dc);
                gmic_apply(images[selection[l]],shift(ndx,ndy,ndz,ndc,boundary));
              }
            } else arg_error("shift");
            is_released = false; ++position; continue;
          }

          // Keep slices.
          if (!std::strcmp("-slices",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind0, ind1;
            float value0 = 0, value1 = 0;
            char sep0 = 0, sep1 = 0;
            *argx = *argy = 0;
            if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-]%c",
                            argx,&end)==1 &&
                ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c]",indices,&sep0,&end)==2 &&
                  sep0==']' &&
                  (ind0=selection2cimg(indices,images.size(),images_names,"-slices",true,
                                       false,CImg<char>::empty())).height()==1) ||
                 std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%'))) {
              if (ind0) { value0 = images[*ind0].depth() - 1.0f; sep0 = 0; }
              print(images,"Keep slice %g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.depth()-1)/100:value0);
                gmic_apply(img,slice(nvalue0));
              }
            } else if (std::sscanf(argument,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                                   argx,argy,&end)==2 &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind0=selection2cimg(indices,images.size(),images_names,"-slices",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argx,"%f%c",&value0,&end)==1 ||
                        (std::sscanf(argx,"%f%c%c",&value0,&sep0,&end)==2 && sep0=='%')) &&
                       ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",formula,&sep0,&end)==2 &&
                         sep0==']' &&
                         (ind1=selection2cimg(formula,images.size(),images_names,"-slices",true,
                                              false,CImg<char>::empty())).height()==1) ||
                        std::sscanf(argy,"%f%c",&value1,&end)==1 ||
                        (std::sscanf(argy,"%f%c%c",&value1,&sep1,&end)==2 && sep1=='%'))) {
              if (ind0) { value0 = images[*ind0].depth() - 1.0f; sep0 = 0; }
              if (ind1) { value1 = images[*ind1].depth() - 1.0f; sep1 = 0; }
              print(images,"Keep slices %g%s..%g%s of image%s.",
                    value0,sep0=='%'?"%":"",
                    value1,sep1=='%'?"%":"",
                    gmic_selection);
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                const int
                  nvalue0 = (int)cimg::round(sep0=='%'?value0*(img.depth()-1)/100:value0),
                  nvalue1 = (int)cimg::round(sep1=='%'?value1*(img.depth()-1)/100:value1);
                gmic_apply(img,slices(nvalue0,nvalue1));
              }
            } else arg_error("slices");
            is_released = false; ++position; continue;
          }

          // Set random generator seed.
          if (!std::strcmp("-srand",item)) {
            gmic_substitute_args();
            double value = 0;
            if (std::sscanf(argument,"%lf%c",
                            &value,&end)==1) {
              print(images,"Set random generator seed to %u.",
                    (unsigned int)value);
              cimg::srand();
              std::srand((unsigned int)value);
              ++position;
            } else {
              print(images,"Set random generator seed to random.");
              cimg::srand();
#if cimg_OS==1
              std::srand((unsigned int)cimg::time()+(unsigned int)getpid());
#elif cimg_OS==2
              std::srand((unsigned int)cimg::time()+(unsigned int)_getpid());
#else // #if cimg_OS==1
              std::srand((unsigned int)cimg::time());
#endif // #if cimg_OS==1
            }
            continue;
          }

#ifdef gmic_float

          // Sub.
          gmic_arithmetic_item("-sub",
                               operator-=,
                               "Subtract %g%s to image%s",
                               value,ssep,gmic_selection,T,
                               operator-=,
                               "Subtract image [%d] to image%s",
                               ind[0],gmic_selection,
                               "Subtract expression %s to image%s",
                               argument_text,gmic_selection,
                               "Subtract image%s");
          // Square root.
          gmic_simple_item("-sqrt",sqrt,"Compute pointwise square root of image%s.");

          // Square.
          gmic_simple_item("-sqr",sqr,"Compute pointwise square function of image%s.");

          // Sign.
          gmic_simple_item("-sign",sign,"Compute pointwise sign of image%s.");

          // Sine.
          gmic_simple_item("-sin",sin,"Compute pointwise sine of image%s.");

          // Sort.
          if (!std::strcmp("-sort",command)) {
            gmic_substitute_args();
            char order = '+', axis = 0;
            if ((std::sscanf(argument,"%c%c",&order,&end)==1 ||
                 (std::sscanf(argument,"%c,%c%c",&order,&axis,&end)==2 &&
                  (axis=='x' || axis=='y' || axis=='z' || axis=='c'))) &&
                (order=='+' || order=='-')) ++position;
            else { order = '+'; axis = 0; }
            if (axis) print(images,"Sort values of image%s in %s order, according to axis '%c'.",
                            gmic_selection,order=='+'?"ascending":"descending",axis);
            else print(images,"Sort values of image%s in %s order.",
                       gmic_selection,order=='+'?"ascending":"descending");
            cimg_forY(selection,l) gmic_apply(images[selection[l]],sort(order=='+',axis));
            is_released = false; continue;
          }

          // Solve.
          if (!std::strcmp("-solve",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                sep==']' &&
                (ind=selection2cimg(indices,images.size(),images_names,"-solve",true,
                                    false,CImg<char>::empty())).height()==1) {
              print(images,"Solve linear system AX = B, with B-vector%s and A-matrix [%d].",
                    gmic_selection,*ind);
              const CImg<T> A = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],solve(A));
            } else arg_error("solve");
            is_released = false; ++position; continue;
          }

          // Shift 3d object, with opposite displacement.
          if (!std::strcmp("-sub3d",command)) {
            gmic_substitute_args();
            float tx = 0, ty = 0, tz = 0;
            if (std::sscanf(argument,"%f%c",
                            &tx,&end)==1 ||
                std::sscanf(argument,"%f,%f%c",
                            &tx,&ty,&end)==2 ||
                std::sscanf(argument,"%f,%f,%f%c",
                            &tx,&ty,&tz,&end)==3) {
              print(images,"Shift 3d object%s with displacement -(%g,%g,%g).",
                    gmic_selection,
                    tx,ty,tz);
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (!images[ind].is_CImg3d(false,message))
                  error(images,
                        "Command 'sub3d': Invalid 3d object [%d], in selected image%s (%s).",
                        ind,gmic_selection,message);
                gmic_apply(images[ind],shift_CImg3d(-tx,-ty,-tz));
              }
            } else arg_error("sub3d");
            is_released = false; ++position; continue;
          }

          // Draw spline.
          if (!std::strcmp("-spline",command)) {
            gmic_substitute_args();
            static char argu0[256], argv0[256], argx1[256], argy1[256], argu1[256], argv1[256];
            *argx = *argy = *argu0 = *argv0 = *argx1 = *argy1 = *argu1 = *argv1 = *color = 0;
            char sepx0 = 0, sepy0 = 0, sepu0 = 0, sepc0 = 0, sepx1 = 0, sepy1 = 0, sepu1 = 0,
              sepc1 = 0, seph = 0;
            float x0 = 0, y0 = 0, u0 = 0, v0 = 0, x1 = 0, y1 = 0, u1 = 0, v1 = 0, opacity = 1;
            unsigned int pattern = ~0U;
            if ((std::sscanf(argument,
                             "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,argu0,argv0,argx1,argy1,argu1,argv1,&end)==8 ||
                 std::sscanf(argument,
                             "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                             "%f%c",
                             argx,argy,argu0,argv0,argx1,argy1,argu1,argv1,&opacity,&end)==9 ||
                 (std::sscanf(argument,
                              "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                              "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,"
                              "0%c%x%c",
                              argx,argy,argu0,argv0,argx1,argy1,argu1,argv1,&opacity,
                              &seph,&pattern,&end)==11 && seph=='x') ||
                 (std::sscanf(argument,
                              "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                              "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,"
                              "%4095[0-9.eE,+-]%c",
                              argx,argy,argu0,argv0,argx1,argy1,argu1,argv1,
                              &opacity,color,&end)==10 &&
                  (pattern=~0U)) ||
                 (*color=0,std::sscanf(argument,
                                       "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                       "%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],"
                                       "%255[0-9.eE%+-],%255[0-9.eE%+-],%f,0%c%x,"
                                       "%4095[0-9.eE,+-]%c",
                                       argx,argy,argu0,argv0,argx1,argy1,argu1,argv1,
                                       &opacity,&seph,&pattern,color,&end)==12 && seph=='x')) &&
                (std::sscanf(argx,"%f%c",&x0,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x0,&sepx0,&end)==2 && sepx0=='%')) &&
                (std::sscanf(argy,"%f%c",&y0,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y0,&sepy0,&end)==2 && sepy0=='%')) &&
                (std::sscanf(argu0,"%f%c",&u0,&end)==1 ||
                 (std::sscanf(argu0,"%f%c%c",&u0,&sepu0,&end)==2 && sepu0=='%')) &&
                (std::sscanf(argv0,"%f%c",&v0,&end)==1 ||
                 (std::sscanf(argv0,"%f%c%c",&v0,&sepc0,&end)==2 && sepc0=='%')) &&
                (std::sscanf(argx1,"%f%c",&x1,&end)==1 ||
                 (std::sscanf(argx1,"%f%c%c",&x1,&sepx1,&end)==2 && sepx1=='%')) &&
                (std::sscanf(argy1,"%f%c",&y1,&end)==1 ||
                 (std::sscanf(argy1,"%f%c%c",&y1,&sepy1,&end)==2 && sepy1=='%')) &&
                (std::sscanf(argu1,"%f%c",&u1,&end)==1 ||
                 (std::sscanf(argu1,"%f%c%c",&u1,&sepu1,&end)==2 && sepu1=='%')) &&
                (std::sscanf(argv1,"%f%c",&v1,&end)==1 ||
                 (std::sscanf(argv1,"%f%c%c",&v1,&sepc1,&end)==2 && sepc1=='%'))) {
              print(images,"Draw spline from (%g%s,%g%s) [%g%s,%g%s] to (%g%s,%g%s) [%g%s,%g%s] "
                    "on image%s, with opacity %g, pattern 0x%x and color (%s).",
                    x0,sepx0=='%'?"%":"",
                    y0,sepy0=='%'?"%":"",
                    u0,sepu0=='%'?"%":"",
                    v0,sepc0=='%'?"%":"",
                    x1,sepx1=='%'?"%":"",
                    y1,sepy1=='%'?"%":"",
                    u1,sepu1=='%'?"%":"",
                    v1,sepc1=='%'?"%":"",
                    gmic_selection,
                    opacity,pattern,
                    *color?color:"default");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]], col(img.spectrum(),1,1,1,0);
                col.fill(color,true);
                const int
                  nx0 = (int)cimg::round(sepx0=='%'?x0*(img.width()-1)/100:x0),
                  ny0 = (int)cimg::round(sepy0=='%'?y0*(img.height()-1)/100:y0),
                  nx1 = (int)cimg::round(sepx1=='%'?x1*(img.width()-1)/100:x1),
                  ny1 = (int)cimg::round(sepy1=='%'?y1*(img.height()-1)/100:y1);
                const float
                  nu0 = sepu0=='%'?u0*(img.width()-1)/100:u0,
                  nv0 = sepc0=='%'?v0*(img.height()-1)/100:v0,
                  nu1 = sepu1=='%'?u1*(img.width()-1)/100:u1,
                  nv1 = sepc1=='%'?v1*(img.height()-1)/100:v1;
                gmic_apply(img,draw_spline(nx0,ny0,nu0,nv0,nx1,ny1,nu1,nv1,
                                           col.data(),opacity,4,pattern));
              }
            } else arg_error("spline");
            is_released = false; ++position; continue;
          }

          // Sharpen.
          if (!std::strcmp("-sharpen",command)) {
            gmic_substitute_args();
            float amplitude = 0, edge = -1, alpha = 0, sigma = 0;
            if ((std::sscanf(argument,"%f%c",
                             &amplitude,&end)==1 ||
                 std::sscanf(argument,"%f,%f%c",
                             &amplitude,&edge,&end)==2 ||
                 std::sscanf(argument,"%f,%f,%f%c",
                             &amplitude,&edge,&alpha,&end)==3 ||
                 std::sscanf(argument,"%f,%f,%f,%f%c",
                             &amplitude,&edge,&alpha,&sigma,&end)==4) &&
                amplitude>=0 && (edge==-1 || edge>=0)) {
              if (edge>=0)
                print(images,"Sharpen image%s with shock filters, amplitude %g, edge %g, "
                      "alpha %g and sigma %g.",
                      gmic_selection,
                      amplitude,
                      edge,
                      alpha,
                      sigma);
              else
                print(images,"Sharpen image%s with inverse diffusion and amplitude %g.",
                      gmic_selection,
                      amplitude);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],sharpen(amplitude,(bool)(edge>=0),
                                                        edge,alpha,sigma));
            } else arg_error("sharpen");
            is_released = false; ++position; continue;
          }

          // Anisotropic PDE-based smoothing.
          if (!std::strcmp("-smooth",command)) {
            gmic_substitute_args();
            float amplitude = 0, sharpness = 0.7f, anisotropy = 0.3f, alpha = 0.6f,
              sigma = 1.1f, dl =0.8f, da = 30.0f, gauss_prec = 2.0f;
            unsigned int interpolation = 0, is_fast_approximation = 1;
            CImg<unsigned int> ind;
            char sep = 0;
            if ((std::sscanf(argument,"%f%c",
                             &amplitude,&end)==1 ||
                 std::sscanf(argument,"%f,%f%c",
                             &amplitude,&sharpness,&end)==2 ||
                 std::sscanf(argument,"%f,%f,%f%c",
                             &amplitude,&sharpness,&anisotropy,&end)==3 ||
                 std::sscanf(argument,"%f,%f,%f,%f%c",
                             &amplitude,&sharpness,&anisotropy,&alpha,&end)==4 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f%c",
                             &amplitude,&sharpness,&anisotropy,&alpha,&sigma,&end)==5 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f,%f%c",
                             &amplitude,&sharpness,&anisotropy,&alpha,&sigma,&dl,&end)==6 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f,%f,%f%c",
                             &amplitude,&sharpness,&anisotropy,&alpha,&sigma,&dl,&da,&end)==7 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f,%f,%f,%f%c",
                             &amplitude,&sharpness,&anisotropy,&alpha,&sigma,&dl,&da,&gauss_prec,
                             &end)==8 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f,%f,%f,%f,%u%c",
                             &amplitude,&sharpness,&anisotropy,&alpha,&sigma,&dl,&da,&gauss_prec,
                             &interpolation,&end)==9 ||
                 std::sscanf(argument,"%f,%f,%f,%f,%f,%f,%f,%f,%u,%u%c",
                             &amplitude,&sharpness,&anisotropy,&alpha,&sigma,&dl,&da,&gauss_prec,
                             &interpolation,&is_fast_approximation,&end)==10) &&
                amplitude>=0 && sharpness>=0 && anisotropy>=0 && anisotropy<=1 && dl>0 &&
                da>=0 && gauss_prec>0 && interpolation<=2 && is_fast_approximation<=1) {
              if (da>0)
                print(images,"Smooth image%s anisotropically, with amplitude %g, sharpness %g, "
                      "anisotropy %g, alpha %g, sigma %g, dl %g, da %g, precision %g, "
                      "%s interpolation and fast approximation %s.",
                      gmic_selection,
                      amplitude,
                      sharpness,
                      anisotropy,
                      alpha,
                      sigma,
                      dl,
                      da,
                      gauss_prec,
                      interpolation==0?"nearest-neighbor":interpolation==1?"linear":"runge-kutta",
                      is_fast_approximation?"enabled":"disabled");
              else
                print(images,"Smooth image%s anisotropically, with %d iterations, sharpness %g, "
                      "anisotropy %g, alpha %g, sigma %g and dt %g.",
                      gmic_selection,
                      (int)amplitude,
                      sharpness,
                      anisotropy,
                      alpha,
                      sigma,
                      dl);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],blur_anisotropic(amplitude,sharpness,anisotropy,
                                                                 alpha,sigma,dl,da,gauss_prec,
                                                                 interpolation,
                                                                 (bool)is_fast_approximation));
            } else if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                                     indices,&sep,&end)==2 && sep==']') ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f%c",
                                    indices,&amplitude,&end)==2 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f%c",
                                    indices,&amplitude,&dl,&end)==3 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%f%c",
                                    indices,&amplitude,&dl,&da,&end)==4 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%f,%f%c",
                                    indices,&amplitude,&dl,&da,&gauss_prec,&end)==5 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%f,%f,%u%c",
                                    indices,&amplitude,&dl,&da,&gauss_prec,
                                    &interpolation,&end)==6 ||
                        std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%f,%f,%f,%f,%u,%u%c",
                                    indices,&amplitude,&dl,&da,&gauss_prec,&interpolation,
                                    &is_fast_approximation,&end)==7) &&
                       (ind=selection2cimg(indices,images.size(),images_names,"-smooth",true,
                                           false,CImg<char>::empty())).height()==1 &&
                       amplitude>=0 && dl>0 && da>=0 && gauss_prec>0 && interpolation<=2 &&
                       is_fast_approximation<=1) {
              const CImg<T> tensors = gmic_image_arg(*ind);
              if (da>0)
                print(images,
                      "Smooth image%s anisotropically, with tensor field [%u], amplitude %g, "
                      "dl %g, da %g, precision %g, %s interpolation and fast approximation %s.",
                      gmic_selection,
                      *ind,
                      amplitude,
                      dl,
                      da,
                      gauss_prec,
                      interpolation==0?"nearest-neighbor":interpolation==1?"linear":"runge-kutta",
                      is_fast_approximation?"enabled":"disabled");
              else
                print(images,
                      "Smooth image%s anisotropically, with tensor field [%u], %d iterations "
                      "and dt %g.",
                      gmic_selection,
                      *ind,
                      (int)amplitude,
                      dl);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],blur_anisotropic(tensors,amplitude,dl,da,
                                                                 gauss_prec,interpolation,
                                                                 is_fast_approximation));
            } else arg_error("smooth");
            is_released = false; ++position; continue;
          }

          // Split 3d objects, into 6 vector images
          // { header,N,vertices,primitives,colors,opacities }
          if (!std::strcmp("-split3d",command)) {
            print(images,"Split 3d object%s into 6 property vectors.",
                  gmic_selection);
            unsigned int off = 0;
            cimg_forY(selection,l) {
              const unsigned int ind = selection[l] + off;
              CImg<T> &img = images[ind];
              if (!img.is_CImg3d(true,message))
                error(images,
                      "Command 'split3d': Invalid 3d object [%d], in selected image%s (%s).",
                      ind-off,gmic_selection,message);
              CImg<char> name = images_names[ind].get_mark();
              CImgList<unsigned int> primitives;
              CImgList<float> colors, opacities;
              CImg<T> vertices;
              if (is_get_version) vertices.assign(img); else img.move_to(vertices);
              vertices.CImg3dtoobject3d(primitives,colors,opacities);
              CImgList<T> split;
              (CImg<T>("CImg3d",1,6)+=0.5f).move_to(split);
              CImg<T>::vector((T)vertices.width(),(T)primitives.size()).move_to(split);
              vertices.transpose().unroll('y').move_to(split);
              CImgList<T> _primitives;
              cimglist_for(primitives,p) {
                CImg<T> primitive = primitives[p];
                CImg<T>::vector((T)primitive.size()).move_to(_primitives);
                primitive.unroll('y').move_to(_primitives);
              }
              primitives.assign();
              (_primitives>'y').move_to(split);
              CImgList<T> _colors;
              cimglist_for(colors,c) {
                CImg<T> color = colors[c];
                if (color.size()==3) color.unroll('y').move_to(_colors);
                else {
                  CImg<T>::vector((T)-128,(T)color.width(),(T)color.height(),(T)color.spectrum()).
                    move_to(_colors);
                  color.unroll('y').move_to(_colors);
                }
              }
              colors.assign();
              (_colors>'y').move_to(split);
              CImgList<T> _opacities;
              cimglist_for(opacities,o) {
                CImg<T> opacity = opacities[o];
                if (opacity.size()==1) opacity.move_to(_opacities);
                else {
                  CImg<T>::vector((T)-128,(T)opacity.width(),(T)opacity.height(),
                                  (T)opacity.spectrum()).
                    move_to(_opacities);
                  opacity.unroll('y').move_to(_opacities);
                }
              }
              opacities.assign();
              (_opacities>'y').move_to(split);
              if (is_get_version) {
                images_names.insert(split.size(),name.copymark());
                split.move_to(images,~0U);
              } else {
                off+=split.size() - 1;
                images_names.remove(ind);
                images_names.insert(split.size(),name.get_copymark(),ind);
                name.move_to(images_names[ind]);
                images.remove(ind); split.move_to(images,ind);
              }
            }
            is_released = false; continue;
          }

          // SVD.
          if (!std::strcmp("-svd",command)) {
            print(images,"Compute SVD decomposition%s of matri%s%s.",
                  selection.height()>1?"s":"",selection.height()>1?"ce":"x",gmic_selection);
            CImg<float> U, S, V;
            unsigned int off = 0;
            cimg_forY(selection,l) {
              const unsigned int ind = selection[l] + off;
              CImg<char> name = images_names[ind].get_mark();
              images[ind].SVD(U,S,V,true,100);
              if (is_get_version) {
                images_names.insert(2,name.copymark());
                name.move_to(images_names);
                U.move_to(images);
                S.move_to(images);
                V.move_to(images);
              } else {
                images_names.insert(2,name.get_copymark(),ind+1);
                name.move_to(images_names[ind]);
                U.move_to(images[ind].assign());
                images.insert(S,ind+1);
                images.insert(V,ind+2);
                off+=2;
              }
            }
            is_released = false; continue;
          }

          // Input 3d sphere.
          if (!std::strcmp("-sphere3d",item)) {
            gmic_substitute_args();
            float radius = 100, recursions = 3;
            if ((std::sscanf(argument,"%f%c",
                             &radius,&end)==1 ||
                 std::sscanf(argument,"%f,%f%c",
                             &radius,&recursions,&end)==2) &&
                recursions>=0) {
              recursions = cimg::round(recursions);
              print(images,"Input 3d sphere, with radius %g and %g recursions.",
                    radius,
                    recursions);
              CImgList<unsigned int> primitives;
              CImg<float> vertices = CImg<T>::sphere3d(primitives,radius,(unsigned int)recursions);
              vertices.object3dtoCImg3d(primitives).move_to(images);
              CImg<char>::string("[3d sphere]").move_to(images_names);
            } else arg_error("sphere3d");
            is_released = false; ++position; continue;
          }

          // Set 3d specular light parameters.
          if (!std::strcmp("-specl3d",item)) {
            gmic_substitute_args();
            float value = 0;
            if (std::sscanf(argument,"%f%c",
                            &value,&end)==1 && value>=0) {
              specular_lightness3d = value;
              print(images,"Set lightness of 3d specular light to %g.",
                    specular_lightness3d);
            } else arg_error("specl3d");
            ++position; continue;
          }

          if (!std::strcmp("-specs3d",item)) {
            gmic_substitute_args();
            float value = 0;
            if (std::sscanf(argument,"%f%c",
                            &value,&end)==1 && value>=0) {
              specular_shininess3d = value;
              print(images,"Set shininess of 3d specular light to %g.",
                    specular_shininess3d);
            }
            else arg_error("specs3d");
            ++position; continue;
          }

          // Sine-cardinal.
          gmic_simple_item("-sinc",sinc,"Compute pointwise sinc function of image%s.");

          // Hyperbolic sine.
          gmic_simple_item("-sinh",sinh,"Compute pointwise hyperpolic sine of image%s.");

          // sRGB to RGB.
          gmic_simple_item("-srgb2rgb",sRGBtoRGB,"Convert image%s from sRGB to RGB color bases.");

          // Extract 3d streamline.
          if (!std::strcmp("-streamline3d",command)) {
            gmic_substitute_args();
            unsigned int interp = 2, is_backward = 0, is_oriented_only = 0;
            float x = 0, y = 0, z = 0, L = 100, dl = 0.1f;
            char sepx = 0, sepy = 0, sepz = 0;
            *formula = 0;
            if ((std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,argz,&end)==3 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f%c",
                             argx,argy,argz,&L,&end)==4 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%f%c",
                             argx,argy,argz,&L,&dl,&end)==5 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%f,%u%c",
                             argx,argy,argz,&L,&dl,&interp,&end)==6 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%f,%u,"
                             "%u%c",
                             argx,argy,argz,&L,&dl,&interp,&is_backward,&end)==7 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%f,%u,"
                             "%u,%u%c",
                             argx,argy,argz,&L,&dl,&interp,&is_backward,
                             &is_oriented_only,&end)==8) &&
                (std::sscanf(argx,"%f%c",&x,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&y,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                (!*argz ||
                 std::sscanf(argz,"%f%c",&z,&end)==1 ||
                 (std::sscanf(argz,"%f%c%c",&z,&sepz,&end)==2 && sepz=='%')) &&
                L>=0 && dl>0 && interp<4 && is_backward<=1 && is_oriented_only<=1) {
              print(images,"Extract 3d streamline from image%s, starting from (%g%s,%g%s,%g%s).",
                    gmic_selection,
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    z,sepz=='%'?"%":"");
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                CImg<T>& img = images[ind];
                const float
                  nx = cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = cimg::round(sepy=='%'?y*(img.height()-1)/100:y),
                  nz = cimg::round(sepz=='%'?z*(img.depth()-1)/100:z);
                CImg<T> vertices = img.get_streamline(nx,ny,nz,L,dl,interp,
                                                      (bool)is_backward,(bool)is_oriented_only);
                CImgList<unsigned int> primitives;
                CImgList<unsigned char> colors;
                if (vertices.width()>1) {
                  primitives.assign(vertices.width()-1,1,2);
                  cimglist_for(primitives,l) { primitives(l,0) = l; primitives(l,1) = l+1; }
                  colors.assign(primitives.size(),1,3,1,1,200);
                } else {
                  vertices.assign();
                  warn(images,
                       "Command 'streamline3d': Empty streamline starting from "
                       "(%g%s,%g%s,%g%s) in image [%u].",
                       x,sepx=='%'?"%":"",
                       y,sepy=='%'?"%":"",
                       z,sepz=='%'?"%":"",
                       ind);
                }
                vertices.object3dtoCImg3d(primitives,colors);
                gmic_apply(img,replace(vertices));
              }
            } else if ((std::sscanf(argument,"'%4095[^']',%f,%f,%f%c",
                                    formula,&x,&y,&z,&end)==4 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f%c",
                                    formula,&x,&y,&z,&L,&end)==5 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f%c",
                                    formula,&x,&y,&z,&L,&dl,&end)==6 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%u%c",
                                    formula,&x,&y,&z,&L,&dl,&interp,&end)==7 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%u,%u%c",
                                    formula,&x,&y,&z,&L,&dl,&interp,&is_backward,&end)==8 ||
                        std::sscanf(argument,"'%4095[^']',%f,%f,%f,%f,%f,%u,%u,%u%c",
                                    formula,&x,&y,&z,&L,&dl,&interp,&is_backward,
                                    &is_oriented_only,&end)==9) &&
                       dl>0 && interp<4) {
              gmic_strreplace(formula);
              print(images,"Extract 3d streamline from formula '%s', starting from (%g,%g,%g).",
                    formula,
                    x,y,z);
              CImg<T> vertices = CImg<T>::streamline((const char *)formula,x,y,z,L,dl,interp,
                                                     (bool)is_backward,(bool)is_oriented_only);
              CImgList<unsigned int> primitives;
              CImgList<unsigned char> colors;
              if (vertices.width()>1) {
                primitives.assign(vertices.width()-1,1,2);
                cimglist_for(primitives,l) { primitives(l,0) = l; primitives(l,1) = l+1; }
                colors.assign(primitives.size(),1,3,1,1,200);
              } else {
                vertices.assign();
                warn(images,
                     "Command 'streamline3d': Empty streamline starting from (%g,%g,%g) "
                     "in expression '%s'.",
                     x,y,z,formula);
              }
              vertices.object3dtoCImg3d(primitives,colors).move_to(images);
              cimg_snprintf(title,sizeof(title),"[3d streamline of '%s' at (%g,%g,%g)]",
                            formula,x,y,z);
              gmic_ellipsize(title,sizeof(title));
              CImg<char>::string(title).move_to(images_names);
            } else arg_error("streamline3d");
            is_released = false; ++position; continue;
          }

          // Compute structure tensor field.
          if (!std::strcmp("-structuretensors",command)) {
            gmic_substitute_args();
            unsigned int scheme = 0;
            if (std::sscanf(argument,"%u%c",&scheme,&end)==1 &&
                scheme<=2) ++position;
            else scheme = 2;
            print(images,"Compute structure tensor field of image%s, with %s scheme.",
                  gmic_selection,
                  scheme==0?"centered":scheme==1?"forward-backward1":"forward-backward2");
            cimg_forY(selection,l) gmic_apply(images[selection[l]],structure_tensors(scheme));
            is_released = false; continue;
          }

          // Select image feature.
          if (!std::strcmp("-select",command)) {
            gmic_substitute_args();
            unsigned int feature_type = 0, X=~0U, Y=~0U, Z=~0U;
            bool is_xyz = false;
            if ((std::sscanf(argument,"%u%c",&feature_type,&end)==1 ||
                 (is_xyz=std::sscanf(argument,"%u,%u,%u,%u%c",&feature_type,&X,&Y,&Z,&end)==4)) &&
                feature_type<=3) {
#if cimg_display==0
              print(images,"Select %s in image%s in interactive mode",
                    feature_type==0?"point":feature_type==1?"segment":feature_type==2?"rectangle":
                    "ellipse",gmic_selection);
              if (verbosity>=0 || is_debug) {
                if (is_xyz) std::fprintf(cimg::output(),", from point (%u,%u,%u)",X,Y,Z);
                std::fprintf(cimg::output()," (skipped, no display support).");
                std::fflush(cimg::output());
              }
#else // #if cimg_display==0
              bool is_available_display = false;
              try {
                is_available_display = (bool)CImgDisplay::screen_width();
              } catch (CImgDisplayException&) {
                print(images,
                      "Select %s in image%s in interactive mode",
                      feature_type==0?"point":feature_type==1?"segment":
                      feature_type==2?"rectangle":"ellipse",gmic_selection);
                if (verbosity>=0 || is_debug) {
                  if (is_xyz) std::fprintf(cimg::output(),", from point (%u,%u,%u)",X,Y,Z);
                  std::fprintf(cimg::output()," (skipped, no display available).");
                  std::fflush(cimg::output());
                }
              }
              if (is_available_display) {
                print(images,"Select %s in image%s in interactive mode",
                      feature_type==0?"point":feature_type==1?"segment":
                      feature_type==2?"rectangle":"ellipse",gmic_selection);
                if (verbosity>=0 || is_debug) {
                  if (is_xyz) std::fprintf(cimg::output(),", from point (%u,%u,%u).",X,Y,Z);
                  else std::fprintf(cimg::output(),".");
                  std::fflush(cimg::output());
                }
                unsigned int XYZ[3];
                XYZ[0] = X; XYZ[1] = Y; XYZ[2] = Z;
                if (instant_window[0])
                  cimg_forY(selection,l) {
                    gmic_apply(images[selection[l]],select(instant_window[0],feature_type,
                                                           is_xyz?XYZ:0));
                  }
                else
                  cimg_forY(selection,l) {
                    gmic_apply(images[selection[l]],select(images_names[selection[l]].data(),
                                                           feature_type,is_xyz?XYZ:0));
                  }
              }
#endif // #if cimg_display==0
            } else arg_error("select");
            is_released = false; ++position; continue;
          }

#endif // #ifdef gmic_float
        } // command1=='s'.

        //----------------------------
        // Commands starting by '-t..'
        //----------------------------
        else if (command1=='t') {

          // Set datatype.
          if (!std::strcmp("-type",item)) {
            typedef unsigned char uchar;
            typedef unsigned short ushort;
            typedef unsigned int uint;
#ifndef gmic_float_only
            gmic_cast(bool,"bool");
            gmic_cast(uchar,"unsigned char");
            gmic_cast(char,"char");
            gmic_cast(ushort,"unsigned short");
            gmic_cast(short,"short");
            gmic_cast(uint,"unsigned int");
            gmic_cast(int,"int");
            gmic_cast(double,"double");
#endif // #ifndef gmic_float_only
            gmic_cast(float,"float");
            arg_error("type");
          }

#ifdef gmic_float

          // Threshold.
          if (!std::strcmp("-threshold",command)) {
            gmic_substitute_args();
            unsigned int is_soft = 0;
            double value = 0;
            char sep = 0;
            if ((std::sscanf(argument,"%lf%c",
                             &value,&end)==1 ||
                 (std::sscanf(argument,"%lf%c%c",
                              &value,&sep,&end)==2 && sep=='%') ||
                 std::sscanf(argument,"%lf,%u%c",
                             &value,&is_soft,&end)==2 ||
                 (std::sscanf(argument,"%lf%c,%u%c",
                              &value,&sep,&is_soft,&end)==3 && sep=='%')) &&
                is_soft<=1) {
              print(images,"%s-threshold image%s by %g%s.",
                    is_soft?"Soft":"Hard",
                    gmic_selection,
                    value,sep=='%'?"%":"");
              cimg_forY(selection,l) {
                CImg<T> &img = images[selection[l]];
                double nvalue = value;
                if (sep=='%' && img) {
                  double vmin = 0, vmax = (double)img.max_min(vmin);
                  nvalue = vmin + (vmax-vmin)*value/100;
                }
                gmic_apply(img,threshold((T)nvalue,(bool)is_soft));
              }
              ++position;
            } else {
#if cimg_display==0
              print(images,
                    "Threshold image%s in interactive mode (skipped, no display support).",
                    gmic_selection);
#else // #if cimg_display==0
              bool is_available_display = false;
              try {
                is_available_display = (bool)CImgDisplay::screen_width();
              } catch (CImgDisplayException&) {
                print(images,
                      "Threshold image%s in interactive mode (skipped, no display available).",
                      gmic_selection);
              }
              if (is_available_display) {
                print(images,"Threshold image%s in interactive mode.",
                      gmic_selection);
                CImgDisplay _disp, &disp = instant_window[0]?instant_window[0]:_disp;
                cimg_forY(selection,l) {
                  CImg<T> &img = images[selection[l]];
                  if (img) {
                    CImg<T> visu = img.depth()>1?img.get_projections2d(img.width()/2,
                                                                       img.height()/2,
                                                                       img.depth()/2).
                      channels(0,cimg::min(3,img.spectrum())-1):
                      img.get_channels(0,cimg::min(3,img.spectrum()-1));
                    const unsigned int
                      w = CImgDisplay::_fitscreen(visu.width(),visu.height(),1,256,-85,false),
                      h = CImgDisplay::_fitscreen(visu.width(),visu.height(),1,256,-85,true);
                    if (disp) disp.resize(w,h,false); else disp.assign(w,h,0,0);
                    double vmin = 0, vmax = (double)img.max_min(vmin), percent = 50;
                    bool stopflag = false, is_clicked = false;
                    int omx = -1, omy = -1;
                    CImg<unsigned char> res;
                    for (disp.show().flush(); !stopflag; ) {
                      const unsigned char white[] = { 255,255,255 }, black[] = { 0,0,0 };
                      const unsigned int key = disp.key();
                      if (!res)
                        disp.display(((res=visu.get_threshold((T)(vmin + percent*(vmax-vmin)/100)).
                                       resize(disp))*=255).
                                     draw_text(0,0,"Threshold %g = %.3g%%",
                                               white,black,0.7f,13,
                                               (double)(vmin + percent*(vmax-vmin)/100),
                                               percent)).
                          set_title("%s (%dx%dx%dx%d)",
                                    gmic_basename(images_names[selection[l]].data()),
                                    img.width(),img.height(),img.depth(),img.spectrum()).wait();
                      const int mx = disp.mouse_x(), my = disp.mouse_y();
                      if (disp.button()) {
                        if (mx>=0 && my>=0 && (mx!=omx || my!=omy)) {
                          percent = (my-16)*100.0/(disp.height()-32);
                          if (percent<0) percent = 0; else if (percent>101) percent = 101;
                          omx = mx; omy = my; res.assign();
                        }
                        is_clicked = true;
                      } else if (is_clicked) break;
                      if (disp.is_closed() || (key && key!=cimg::keyCTRLLEFT)) stopflag = true;
                      if (key==cimg::keyD && disp.is_keyCTRLLEFT()) {
                        disp.resize(cimg_fitscreen(3*disp.width()/2,3*disp.height()/2,1),
                                    stopflag=false).set_key(cimg::keyD,false);
                        res.assign();
                      }
                      if (key==cimg::keyC && disp.is_keyCTRLLEFT()) {
                        disp.resize(cimg_fitscreen(2*disp.width()/3,2*disp.height()/3,1),
                                    stopflag=false).set_key(cimg::keyC,false);
                        res.assign();
                      }
                      if (disp.is_resized()) { disp.resize(false); res.assign(); }
                    }
                    print(images,"Hard-threshold image [%d] by %g = %.3g%%.",
                          selection[l],(double)(vmin + percent*(vmax-vmin)/100),percent);
                    gmic_apply(img,threshold((T)(vmin + percent*(vmax-vmin)/100)));
                  } else { gmic_apply(img,replace(img)); }
                }
              }

#endif // #if cimg_display==0
            }
            is_released = false; continue;
          }

          // Tangent.
          gmic_simple_item("-tan",tan,"Compute pointwise tangent of image%s.");

          // Draw text.
          if (!std::strcmp("-text",command)) {
            gmic_substitute_args();
            static char text[4096];
            *argx = *argy = *text = *color = 0;
            float x = 0, y = 0, opacity = 1, siz = 13;
            char sepx = 0, sepy = 0;
            if ((std::sscanf(argument,"%4095[^,]%c",
                             text,&end)==1 ||
                 std::sscanf(argument,"%4095[^,],%255[0-9.eE%+-]%c",
                             text,argx,&end)==2 ||
                 std::sscanf(argument,"%4095[^,],%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             text,argx,argy,&end)==3 ||
                 std::sscanf(argument,"%4095[^,],%255[0-9.eE%+-],%255[0-9.eE%+-],%f%c",
                             text,argx,argy,&siz,&end)==4 ||
                 std::sscanf(argument,"%4095[^,],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%f%c",
                             text,argx,argy,&siz,&opacity,&end)==5 ||
                 std::sscanf(argument,"%4095[^,],%255[0-9.eE%+-],%255[0-9.eE%+-],%f,%f,"
                             "%4095[0-9.eE,+-]%c",
                             text,argx,argy,&siz,&opacity,color,&end)==6) &&
                (!*argx ||
                 std::sscanf(argx,"%f%c",&x,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&x,&sepx,&end)==2 && sepx=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&y,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&y,&sepy,&end)==2 && sepy=='%')) &&
                siz>=0) {
              siz = cimg::round(siz);
              gmic_strreplace(text);
              print(images,"Draw text '%s' at position (%g%s,%g%s) on image%s, with font "
                    "height %g, opacity %g and color (%s).",
                    text,
                    x,sepx=='%'?"%":"",
                    y,sepy=='%'?"%":"",
                    gmic_selection,
                    siz,
                    opacity,
                    *color?color:"default");
              cimg::strunescape(text);
              unsigned int nb_cols = 1;
              for (const char *s = color; *s; ++s) if (*s==',') ++nb_cols;
              cimg_forY(selection,l) {
                CImg<T>
                  &img = images[selection[l]],
                  col(cimg::max(img.spectrum(),(int)nb_cols),1,1,1,0);
                col.fill(color,true);
                const int
                  nx = (int)cimg::round(sepx=='%'?x*(img.width()-1)/100:x),
                  ny = (int)cimg::round(sepy=='%'?y*(img.height()-1)/100:y);
                gmic_apply(img,gmic_draw_text(nx,ny,text,col,0,opacity,(unsigned int)siz,nb_cols));
              }
            } else arg_error("text");
            is_released = false; ++position; continue;
          }

          // Texturize 3d object.
          if (!std::strcmp("-texturize3d",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind_texture, ind_coords;
            char sep = 0;
            *argx = *argy = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              argx,&sep,&end)==2 && sep==']') ||
                 (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],[%255[a-zA-Z0-9_.%+-]%c%c",
                              argx,argy,&sep,&end)==3 && sep==']')) &&
                (ind_texture=selection2cimg(argx,images.size(),images_names,"-texturize3d",true,
                                            false,CImg<char>::empty())).height()==1 &&
                (!*argy || (ind_coords=selection2cimg(argy,images.size(),images_names,
                                                      "-texturize3d",true,
                                                      false,CImg<char>::empty())).height()==1)) {
              if (ind_coords)
                print(images,
                      "Texturize 3d object%s with texture [%u] and texture coordinates [%u].",
                      gmic_selection,*ind_texture,*ind_coords);
              else
                print(images,"Texturize 3d object%s with texture [%u].",
                      gmic_selection,*ind_texture);
              const CImg<T>
                texture = gmic_image_arg(*ind_texture),
                coords = ind_coords?gmic_image_arg(*ind_coords):CImg<T>();
              cimg_forY(selection,l) {
                const unsigned int ind = selection[l];
                if (!images[ind].is_CImg3d(false,message))
                  error(images,"Command 'texturize3d': Invalid 3d object [%d], "
                        "in selected image%s (%s).",
                        ind,gmic_selection,message);
                gmic_apply(images[ind],texturize_CImg3d(texture,coords));
              }
            } else arg_error("texturize3d");
            is_released = false; ++position; continue;
          }

          // Tridiagonal solve.
          if (!std::strcmp("-trisolve",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind;
            char sep = 0;
            if (std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                sep==']' &&
                (ind=selection2cimg(indices,images.size(),images_names,"-trisolve",true,
                                    false,CImg<char>::empty())).height()==1) {
              print(images,"Solve tridiagonal system AX = B, with B-vector%s and tridiagonal "
                    "A-matrix [%d].",
                    gmic_selection,*ind);
              const CImg<T> A = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],solve_tridiagonal(A));
            } else arg_error("trisolve");
            is_released = false; ++position; continue;
          }

          // Hyperbolic tangent.
          gmic_simple_item("-tanh",tanh,"Compute pointwise hyperbolic tangent of image%s.");

#endif // #ifdef gmic_float
        } // command1=='t'.

        //----------------------------
        // Commands starting by '-u..'
        //----------------------------
        else if (command1=='u') {

          // Unroll.
          if (!std::strcmp("-unroll",command)) {
            gmic_substitute_args();
            const char axis = *argument;
            if (std::strlen(argument)==1 &&
                (axis=='x' || axis=='y' || axis=='z' || axis=='c')) {
              print(images,"Unroll image%s along the '%c'-axis.",
                    gmic_selection,
                    axis);
              cimg_forY(selection,l) gmic_apply(images[selection[l]],unroll(axis));
            } else arg_error("unroll");
            is_released = false; ++position; continue;
          }

          // Remove custom command.
          if (!std::strcmp("-uncommand",item)) {
            gmic_substitute_args();
            if (argument[0]=='*' && !argument[1]) { // Discard all custom commands.
              unsigned int nb_commands = 0;
              for (unsigned int i = 0; i<256; ++i) {
                nb_commands+=commands[i].size();
                commands[i].assign();
                commands_names[i].assign();
                commands_has_arguments[i].assign();
              }
              print(images,"Discard definitions of all custom commmands (%u command%s discarded).",
                    nb_commands,nb_commands>1?"s":"");
            } else { // Discard a single custom command.
              print(images,"Discard last definition of custom command '%s'",argument_text);
              CImg<char> arg_command(argument,std::strlen(argument)+1);
              gmic_strreplace(arg_command);
              bool is_removed = false;
              if (*arg_command) {
                const int ind = gmic_hashcode(arg_command,false);
                cimglist_for(commands_names[ind],l)
                  if (!std::strcmp(commands_names[ind][l],arg_command)) {
                    commands_names[ind].remove(l);
                    commands[ind].remove(l);
                    commands_has_arguments[ind].remove(l);
                    is_removed = true; break;
                  }
              }
              if (verbosity>=0 || is_debug) {
                unsigned int siz = 0;
                for (unsigned int l = 0; l<256; ++l) siz+=commands[l].size();
                std::fprintf(cimg::output()," (%s, %u command%s left).",
                             is_removed?"found":"not found",siz,siz>1?"s":"");
                std::fflush(cimg::output());
              }
            }
            ++position; continue;
          }

        } // command1=='u'.

        //----------------------------
        // Commands starting by '-v..'
        //----------------------------
        else if (command1=='v') {

          // Set verbosity (actually only display something, since it has already been processed).
          if (!std::strcmp("-verbose",item)) {
            if (*argument=='+' && !argument[1]) {
              if (verbosity>0) print(images,"Increment verbosity level (set to %d).",
                                     verbosity);
            } else if (*argument=='-' && !argument[1])
              print(images,"Decrement verbosity level (set to %d).",
                    verbosity);
            else
              if (verbosity>0) print(images,"Set verbosity level to %d.",
                                     verbosity);
            ++position; continue;
          }

          // Vanvliet filter.
          if (!std::strcmp("-vanvliet",command)) {
            gmic_substitute_args();
            unsigned int boundary = 1, order = 0;
            char sep = 0, axis = 0;
            float sigma = 0;
            if ((std::sscanf(argument,"%f,%u,%c%c",&sigma,&order,&axis,&end)==3 ||
                 (std::sscanf(argument,"%f%c,%u,%c%c",&sigma,&sep,&order,&axis,&end)==4 &&
                  sep=='%') ||
                 std::sscanf(argument,"%f,%u,%c,%u%c",&sigma,&order,&axis,&boundary,&end)==4 ||
                 (std::sscanf(argument,"%f%c,%u,%c,%u%c",
                              &sigma,&sep,&order,&axis,&boundary,&end)==5 && sep=='%')) &&
                sigma>=0 && order<=3 && (axis=='x' || axis=='y' || axis=='z' || axis=='c') &&
                boundary<=1) {
              print(images,"Apply Vanvliet filter on image%s, with standard "
                    "deviation %g%s, order %d, axis '%c' and %s boundary.",
                    gmic_selection,
                    sigma,sep=='%'?"%":"",
                    order,axis,
                    boundary?"neumann":"dirichlet");
              if (sep=='%') sigma = -sigma;
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],vanvliet(sigma,order,axis,(bool)boundary));
            } else arg_error("vanvliet");
            is_released = false; ++position; continue;
          }

        } // command1=='v'.

        //----------------------------
        // Commands starting by '-w..'
        //----------------------------
        else if (command1=='w') {

          // While.
          if (!std::strcmp("-while",item)) {
            gmic_substitute_args();
            const CImg<char> &s = scope.back();
            if (s[0]!='*' || s[1]!='d')
              error(images,
                    "Command 'while': Not associated to a 'do' command within the same scope.");
            float _is_cond = 0;
            if (std::sscanf(argument,"%f%c",&_is_cond,&end)!=1) {
              CImg<char> arg_while(argument,std::strlen(argument)+1);
              gmic_strreplace(arg_while);
              _is_cond = 0;
              try {
                std::FILE *file = cimg::fopen(arg_while,"r");
                if (file) { _is_cond = 1; cimg::fclose(file); }
              } catch (CImgException&) {}
            }
            const bool is_cond = (bool)_is_cond;
            if (is_cond) { position = dowhiles.back()(0); continue; }
            else {
              if (verbosity>0 || is_debug) print(images,"End 'do..while' block.");
              dowhiles.remove();
              scope.remove();
            }
            ++position; continue;
          }

          // Warning.
          if (!std::strcmp("-warn",command)) {
            gmic_substitute_args();
            CImg<char> str(argument,std::strlen(argument)+1);
            cimg::strunescape(str);
            if (is_restriction) warn(images,selection,"%s",str.data());
            else warn(images,"%s",str.data());
            ++position; continue;
          }

#ifdef gmic_float

          // Display images in instant display window.
          unsigned int wind = 0;
          if ((!std::strcmp("-window",command) ||
               std::sscanf(command,"-window%u%c",&wind,&end)==1 ||
               std::sscanf(command,"-w%u%c",&wind,&end)==1) &&
              wind<10) {
            gmic_substitute_args();
            *title = 0;
            int norm = -1, fullscreen = -1;
            float dimw = -1, dimh = -1;
            char sepw = 0, seph = 0;
            *argx = *argy = 0;
            if ((std::sscanf(argument,"%255[0-9.eE%+-]%c",
                             argx,&end)==1 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-]%c",
                             argx,argy,&end)==2 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%d%c",
                             argx,argy,&norm,&end)==3 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%d,%d%c",
                             argx,argy,&norm,&fullscreen,&end)==4 ||
                 std::sscanf(argument,"%255[0-9.eE%+-],%255[0-9.eE%+-],%d,%d,%255[^\n]",
                             argx,argy,&norm,&fullscreen,title)==5) &&
                (std::sscanf(argx,"%f%c",&dimw,&end)==1 ||
                 (std::sscanf(argx,"%f%c%c",&dimw,&sepw,&end)==2 && sepw=='%')) &&
                (!*argy ||
                 std::sscanf(argy,"%f%c",&dimh,&end)==1 ||
                 (std::sscanf(argy,"%f%c%c",&dimh,&seph,&end)==2 && seph=='%')) &&
                (dimw>=0 || dimw==-1) &&
                (dimh>=0 || dimh==-1) &&
                norm>=-1 && norm<=3) ++position;
            else { dimw = dimh = -1; norm = fullscreen = -1; sepw = seph = 0; }
            if (dimh==0) dimw = 0;
            gmic_strreplace(title);
            cimg::strunescape(title);

            // Get images to display and compute associated optimal size.
            unsigned int optw = 0, opth = 0;
            CImgList<T> subimages;
            if (dimw && dimh) cimg_forY(selection,l) {
                const CImg<T> &img = images[selection[l]];
                if (img) {
                  subimages.insert(img,~0U,true);
                  optw+=img.width() + (img.depth()>1?img.depth():0);
                  if (img.height()>(int)opth) opth = img.height() + (img.depth()>1?img.depth():0);
                }
              }
            optw = optw?optw:sepw=='%'?CImgDisplay::screen_width():256;
            opth = opth?opth:seph=='%'?CImgDisplay::screen_height():256;
            dimw = dimw<0?-1:cimg::round(sepw=='%'?optw*dimw/100:dimw);
            dimh = dimh<0?-1:cimg::round(seph=='%'?opth*dimh/100:dimh);

#if cimg_display==0
            print(images,
                  "Display image%s in instant window [%d] (skipped, no display support).",
                  gmic_selection,
                  wind);
#else // #if cimg_display==0
            bool is_available_display = false;
            try {
              is_available_display = (bool)CImgDisplay::screen_width();
            } catch (CImgDisplayException&) {
              print(images,
                    "Display image%s in instant window [%d] (skipped, no display available).",
                    gmic_selection,
                    wind);
            }
            if (is_available_display) {

              if (!dimw || !dimh) { // Close.
                print(images,"Close instant window [%d].",
                      wind);
                instant_window[wind].assign();
              } else {
                if (instant_window[wind]) { // Update.
                  instant_window[wind].resize(dimw>0?(int)dimw:instant_window[wind].window_width(),
                                              dimh>0?(int)dimh:instant_window[wind].window_height(),
                                              false);
                  if (norm>=0) instant_window[wind]._normalization = norm;
                  if (*title && std::strcmp(instant_window[wind].title(),title))
                    instant_window[wind].set_title("%s",title);
                  if (fullscreen>=0 && (bool)fullscreen!=instant_window[wind].is_fullscreen())
                    instant_window[wind].toggle_fullscreen(false);
                } else { // Create.
                  instant_window[wind].assign(dimw>0?(int)dimw:optw,
                                              dimh>0?(int)dimh:opth,
                                              title,norm<0?3:norm,
                                              fullscreen<0?false:(bool)fullscreen);
                  if (norm==2) {
                    if (subimages)
                      instant_window[wind]._max = (float)subimages.max_min(instant_window[wind]._min);
                    else { instant_window[wind]._min = 0; instant_window[wind]._max = 255; }
                  }
                }
                print(images,
                      "Display image%s in %dx%d %sinstant window [%d], with%snormalization, "
                      "%sfullscreen and title '%s'.",
                      gmic_selection,
                      instant_window[wind].width(),
                      instant_window[wind].height(),
                      instant_window[wind].is_fullscreen()?"fullscreen ":"",
                      wind,
                      instant_window[wind].normalization()==0?"out ":
                      instant_window[wind].normalization()==1?" ":
                      instant_window[wind].normalization()==2?" 1st-time ":" auto-",
                      instant_window[wind].is_fullscreen()?"":"no ",
                      instant_window[wind].title());
                if (subimages) subimages.display(instant_window[wind]);
              }
            }

#endif // #if cimg_display==0
            is_released = true; continue;
          }

          // Warp.
          if (!std::strcmp("-warp",command)) {
            gmic_substitute_args();
            unsigned int interpolation = 1, is_relative = 0, boundary = 1;
            CImg<unsigned int> ind;
            float nb_frames = 1;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",
                              indices,&sep,&end)==2 && sep==']')||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u%c",
                             indices,&is_relative,&end)==2 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u%c",
                             indices,&is_relative,&interpolation,&end)==3 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u,%u%c",
                             indices,&is_relative,&interpolation,&boundary,&end)==4 ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u,%u,%u,%f%c",
                             indices,&is_relative,&interpolation,&boundary,&nb_frames,&end)==5) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-warp",true,
                                    false,CImg<char>::empty())).height()==1 &&
                is_relative<=1 && interpolation<=1 && boundary<=2 && nb_frames>=0.5) {
              const CImg<T> warping_field = gmic_image_arg(*ind);
              nb_frames = cimg::round(nb_frames);
              if (nb_frames==1) {
                print(images,"Warp image%s with %s displacement field [%u], %s interpolation, "
                      "%s boundary.",
                      gmic_selection,
                      is_relative?"relative":"absolute",*ind,
                      interpolation?"linear":"nearest-neighbor",
                      boundary==0?"dirichlet":boundary==1?"neumann":"cyclic");
                cimg_forY(selection,l)
                  gmic_apply(images[selection[l]],warp(warping_field,(bool)is_relative,
                                                       (bool)interpolation,boundary));
              } else {
                print(images,"Warp image%s with %s displacement field [%u], %s interpolation, "
                      "%s boundary and %d frames.",
                      gmic_selection,
                      is_relative?"relative":"absolute",*ind,
                      interpolation?"linear":"nearest-neighbor",
                      boundary==0?"dirichlet":boundary==1?"neumann":"cyclic",
                      (int)nb_frames);
                unsigned int off = 0;
                cimg_forY(selection,l) {
                  const unsigned int _ind = selection[l] + off;
                  CImg<T> &img = images[_ind];
                  CImg<char> name = images_names[_ind].get_mark();
                  CImgList<T> frames((int)nb_frames);
                  cimglist_for(frames,t)
                    frames[t] = img.get_warp(warping_field*((t+1.0f)/nb_frames),(bool)is_relative,
                                             (bool)interpolation,boundary);
                  if (is_get_version) {
                    images_names.insert((int)nb_frames,name.copymark());
                    frames.move_to(images,~0U);
                  } else {
                    off+=(int)nb_frames - 1;
                    images_names.insert((int)nb_frames - 1,name.get_copymark(),_ind);
                    images.remove(_ind); frames.move_to(images,_ind);
                  }
                }
              }
            } else arg_error("warp");
            is_released = false; ++position; continue;
          }

          // Watershed transform.
          if (!std::strcmp("-watershed",command)) {
            gmic_substitute_args();
            CImg<unsigned int> ind;
            unsigned int is_filled = 1;
            char sep = 0;
            if (((std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sep,&end)==2 &&
                  sep==']') ||
                 std::sscanf(argument,"[%255[a-zA-Z0-9_.%+-]],%u%c",
                             indices,&is_filled,&end)==2) &&
                (ind=selection2cimg(indices,images.size(),images_names,"-watershed",true,
                                    false,CImg<char>::empty())).height()==1 &&
                is_filled<=1) {
              print(images,"Compute watershed transform of image%s with priority map [%u] and "
                    "%sfilling.",
                    gmic_selection,*ind,is_filled?"":"no ");
              const CImg<T> priority = gmic_image_arg(*ind);
              cimg_forY(selection,l)
                gmic_apply(images[selection[l]],watershed(priority,(bool)is_filled));
            } else arg_error("watershed");
            is_released = false; ++position; continue;
          }

          // Wait for a given delay of for user events on instant window.
          if (!std::strcmp("-wait",command)) {
            gmic_substitute_args();
            if (!is_restriction)
              CImg<unsigned int>::vector(0,1,2,3,4,5,6,7,8,9).move_to(selection);
            float delay = 0;
            if (std::sscanf(argument,"%f%c",
                            &delay,&end)==1) ++position;
            else delay = 0;
            delay = cimg::round(delay);
#if cimg_display==0
            if (!delay)
              print(images,
                    "Wait for user events on instant window%s (skipped, no display support).",
                    gmic_selection);
            else {
              print(images,
                    "Wait for %g milliseconds according to instant window%s.",
                    delay,
                    gmic_selection);
              cimg::wait((unsigned int)(delay<0?-delay:delay));
            }
#else // #if cimg_display==0
            if (!delay) {
              print(images,"Wait for user events on instant window%s.",
                    gmic_selection);
              CImgDisplay *const iw = instant_window;
              switch (selection.height()) {
              case 1 : CImgDisplay::wait(iw[selection[0]]); break;
              case 2 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]]); break;
              case 3 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]]);
                break;
              case 4 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]],
                                         iw[selection[3]]);
                break;
              case 5 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]],
                                         iw[selection[3]],iw[selection[4]]);
                break;
              case 6 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]],
                                         iw[selection[3]],iw[selection[4]],iw[selection[5]]);
                break;
              case 7 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]],
                                         iw[selection[3]],iw[selection[4]],iw[selection[5]],
                                         iw[selection[6]]);
                break;
              case 8 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]],
                                         iw[selection[3]],iw[selection[4]],iw[selection[5]],
                                         iw[selection[6]],iw[selection[7]]);
                break;
              case 9 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]],
                                         iw[selection[3]],iw[selection[4]],iw[selection[5]],
                                         iw[selection[6]],iw[selection[7]],iw[selection[8]]);
                break;
              case 10 : CImgDisplay::wait(iw[selection[0]],iw[selection[1]],iw[selection[2]],
                                          iw[selection[3]],iw[selection[4]],iw[selection[5]],
                                          iw[selection[6]],iw[selection[7]],iw[selection[8]],
                                          iw[selection[9]]);
                break;
              }
            } else if (delay<0) {
              print(images,
                    "Flush display events of instant window%s and wait for %g milliseconds.",
                    gmic_selection,-delay);
              cimg_forY(selection,l) instant_window[selection[l]].flush();
              if (selection && instant_window[selection[0]])
                instant_window[selection[0]].wait((unsigned int)-delay);
              else cimg::wait((unsigned int)-delay);
            } else {
              print(images,"Wait for %g milliseconds according to instant window%s",
                    delay,
                    gmic_selection);
              if (selection && instant_window[selection[0]])
                instant_window[selection[0]].wait((unsigned int)delay);
              else cimg::wait((unsigned int)delay);
            }
#endif // #if cimg_display==0
            continue;
          }

#endif // #ifdef gmic_float
        } // command1=='w'.

        //----------------------------
        // Commands starting by '-x..'
        //----------------------------
        else if (command1=='x') {

#ifdef gmic_float

          // Bitwise xor.
          gmic_arithmetic_item("-xor",
                               operator^=,
                               "Compute bitwise XOR of image%s by %g%s",
                               gmic_selection,value,ssep,T,
                               operator^=,
                               "Compute bitwise XOR of image%s by image [%d]",
                               gmic_selection,ind[0],
                               "Compute bitwise XOR of image%s by expression %s",
                               gmic_selection,argument_text,
                               "Compute sequential bitwise XOR of image%s");

#endif // #ifdef gmic_float
        } // command1=='x'.

        //----------------------------
        // Other (special) commands.
        //----------------------------

        // If..[elif]..[else]..endif.
        if (!std::strcmp("-if",item) || (!std::strcmp("-elif",item) && check_elif)) {
          gmic_substitute_args();
          check_elif = false;
          float _is_cond = 0;
          bool is_filename = false;
          if (std::sscanf(argument,"%f%c",&_is_cond,&end)!=1) {
            is_filename = true;
            CImg<char> arg_if(argument,std::strlen(argument)+1);
            gmic_strreplace(arg_if);
            _is_cond = 0;
            try {
              std::FILE *file = cimg::fopen(arg_if,"r");
              if (file) { _is_cond = 1; cimg::fclose(file); }
            } catch (CImgException&) {}
          }
          const bool is_cond = (bool)_is_cond;
          if (item[1]=='i') {
            CImg<char>::string("*if").move_to(scope);
            if (verbosity>0 || is_debug) print(images,"Start 'if..endif' block -> %s '%s' %s.",
                                               is_filename?"filename":"boolean",
                                               argument_text,
                                               is_filename?(is_cond?"exists":"does not exist"):
                                               (is_cond?"is true":"is false"));
          } else if (verbosity>0 || is_debug) print(images,"Reach 'elif' block -> %s '%s' %s.",
                                                    is_filename?"filename":"boolean",
                                                    argument_text,
                                                    is_filename?(is_cond?"exists":
                                                                 "does not exist"):
                                                    (is_cond?"is true":"is false"));
          if (!is_cond) {
            for (int nb_ifs = 1; nb_ifs && position<commands_line.size(); ++position) {
              const char *const it = commands_line[position].data();
              if (!std::strcmp("-if",it)) ++nb_ifs;
              else if (!std::strcmp("-endif",it)) { --nb_ifs; if (!nb_ifs) --position; }
              else if (nb_ifs==1) {
                if (!std::strcmp("-else",it)) --nb_ifs;
                else if (!std::strcmp("-elif",it)) { --nb_ifs; check_elif = true; --position;}
              }
            }
            continue;
          }
          ++position; continue;
        }

        // Break and continue.
        bool is_continue = false;
        if (!std::strcmp("-break",item) ||
            (!std::strcmp("-continue",item) && (is_continue=true)==true)) {
          const char
            *const com = is_continue?"continue":"break",
            *const Com = is_continue?"Continue":"Break";
          unsigned int scope_repeat = 0, scope_do = 0, scope_local = 0;
          for (unsigned int l = scope.size() - 1; l; --l) {
            const char *const s = scope[l].data();
            if (s[0]=='*' && s[1]=='r') { scope_repeat = l; break; }
            else if (s[0]=='*' && s[1]=='d') { scope_do = l; break; }
            else if (s[0]=='*' && s[1]=='l') { scope_local = l; break; }
            else if (s[0]!='*' || s[1]!='i') break;
          }
          const char *stb = 0, *ste = 0;
          unsigned int scope_ind = 0;
          int level = 0;
          if (scope_repeat) {
            print(images,"%s %scurrent 'repeat..done' block.",
                  Com,is_continue?"to next iteration of ":"");
            for (level = 1; level && position<commands_line.size(); ++position) {
              const char *it = commands_line[position].data();
              if (!std::strcmp("-repeat",it)) ++level;
              else if (!std::strcmp("-done",it)) --level;
            }
            scope_ind = scope_repeat;
            stb = "repeat"; ste = "done";
          } else if (scope_do) {
            print(images,"%s %scurrent 'do..while' block.",
                  Com,is_continue?"to next iteration of ":"");
            for (level = 1; level && position<commands_line.size(); ++position) {
              const char *it = commands_line[position].data();
              if (!std::strcmp("-do",it)) ++level;
              else if (!std::strcmp("-while",it)) --level;
            }
            scope_ind = scope_do;
            stb = "do"; ste = "while";
          } else if (scope_local) {
            print(images,"%s %scurrent local environment.",
                  Com,is_continue?"to end of ":"");
            for (level = 1; level && position<commands_line.size(); ++position) {
              const char *it = commands_line[position].data();
              if (!std::strcmp("-local",it) || !std::strcmp("-l",it) ||
                  !std::strcmp("--local",it) || !std::strcmp("--l",it) ||
                  !std::strncmp("-local[",it,7) || !std::strncmp("-l[",it,3) ||
                  !std::strncmp("--local[",it,8) || !std::strncmp("--l[",it,4)) ++level;
              else if (!std::strcmp("-endlocal",it) || !std::strcmp("-endl",it)) --level;
            }
            scope_ind = scope_local;
            stb = "local"; ste = "endlocal";
          } else {
            print(images,"%s",Com);
            error(images,"Command '%s': There are no loops or local environment to %s.",com,com);
            continue;
          }
          if (level && position>=commands_line.size())
            error(images,"Command '%s': Missing associated '%s' command.",stb,ste);
          if (is_continue || scope_local) {
            if (scope_ind<scope.size()-1) scope.remove(scope_ind+1,scope.size()-1);
            --position;
          } else {
            scope.remove(scope_ind,scope.size()-1);
            if (scope_do) { dowhiles.remove(); ++position; } else repeatdones.remove();
          }
          continue;
        }

        // Quit.
        if (!std::strcmp("-quit",item) || *cancel) {
          print(images,"Quit G'MIC instance.\n");
          dowhiles.assign();
          repeatdones.assign();
          position = commands_line.size();
          is_released = is_quit = true;
          break;
        }

#ifdef gmic_float

        // Compute direct or inverse FFT.
        const bool inv_fft = !std::strcmp("-ifft",command);
        if (!std::strcmp("-fft",command) || inv_fft) {
          print(images,"Compute %sfourier transform of image%s with complex pair%s",
                inv_fft?"inverse ":"",
                gmic_selection,
                selection.height()>2?"s":"");
          cimg_forY(selection,l) {
            const unsigned int
              ind0 = selection[l],
              ind1 = l+1<selection.height()?selection[l+1]:~0U;
            CImg<char> name = images_names[ind0].get_mark();
            if (ind1!=~0U) { // Complex transform.
              if (verbosity>=0 || is_debug) {
                std::fprintf(cimg::output()," ([%u],[%u])%c",ind0,ind1,
                             l>=selection.height()-2?'.':',');
                std::fflush(cimg::output());
              }
              if (is_get_version) {
                CImgList<T> fft(images[ind0],images[ind1]);
                fft.FFT(inv_fft);
                fft.move_to(images,~0U);
                images_names.insert(2,name.copymark());
              } else {
                CImgList<T> fft(2);
                fft[0].swap(images[ind0]);
                fft[1].swap(images[ind1]);
                fft.FFT(inv_fft);
                fft[0].swap(images[ind0]);
                fft[1].swap(images[ind1]);
                name.get_copymark().move_to(images_names[ind1]);
                name.move_to(images_names[ind0]);
              }
              ++l;
            } else { // Real transform.
              if (verbosity>=0 || is_debug) {
                std::fprintf(cimg::output()," ([%u],0)",ind0);
                std::fflush(cimg::output());
              }
              if (is_get_version) {
                CImgList<T> fft(images[ind0]);
                CImg<T>(fft[0].width(),fft[0].height(),fft[0].depth(),fft[0].spectrum(),0).
                  move_to(fft);
                fft.FFT(inv_fft);
                fft.move_to(images,~0U);
                images_names.insert(2,name.copymark());
              } else {
                CImgList<T> fft(1);
                fft[0].swap(images[ind0]);
                CImg<T>(fft[0].width(),fft[0].height(),fft[0].depth(),fft[0].spectrum(),0).
                  move_to(fft);
                fft.FFT(inv_fft);
                fft[0].swap(images[ind0]);
                fft[1].move_to(images,ind0+1);
                name.get_copymark().move_to(images_names,ind0+1);
                name.move_to(images_names[ind0]);
              }
            }
          }
          is_released = false; continue;
        }

        // Compute haar transform.
        const bool inv_haar = !std::strcmp("-ihaar",command);
        if (!std::strcmp("-haar",command) || inv_haar) {
          gmic_substitute_args();
          float nb_scales = 0;
          if (std::sscanf(argument,"%f%c",
                          &nb_scales,&end)==1 &&
              nb_scales>0) {
            nb_scales = cimg::round(nb_scales);
            print(images,"Compute %shaar transform of image%s with %g scales.",
                  inv_haar?"inverse ":"",
                  gmic_selection,
                  nb_scales);
            cimg_forY(selection,l)
              gmic_apply(images[selection[l]],haar(inv_haar,(unsigned int)nb_scales));
          } else arg_error(command);
          is_released = false; ++position; continue;
        }

        // Inverse scale of a 3d object.
        const bool divide3d = !std::strcmp("-div3d",command);
        if (!std::strcmp("-mul3d",command) || divide3d) {
          gmic_substitute_args();
          float sx = 0, sy = 1, sz = 1;
          if ((std::sscanf(argument,"%f%c",
                           &sx,&end)==1 && ((sz=sy=sx),1)) ||
              std::sscanf(argument,"%f,%f%c",
                          &sx,&sy,&end)==2 ||
              std::sscanf(argument,"%f,%f,%f%c",
                          &sx,&sy,&sz,&end)==3) {
            if (divide3d)
              print(images,"Scale 3d object%s with factors (1/%g,1/%g,1/%g).",
                    gmic_selection,
                    sx,sy,sz);
            else
              print(images,"Scale 3d object%s with factors (%g,%g,%g).",
                    gmic_selection,
                    sx,sy,sz);
            cimg_forY(selection,l) {
              const unsigned int ind = selection[l];
              if (!images[ind].is_CImg3d(false,message))
                error(images,"Command '%s3d': Invalid 3d object [%d], in selected image%s (%s).",
                      divide3d?"div":"mul",ind,gmic_selection,message);
              if (divide3d) { gmic_apply(images[ind],scale_CImg3d(1/sx,1/sy,1/sz)); }
              else { gmic_apply(images[ind],scale_CImg3d(sx,sy,sz)); }
            }
          } else { if (divide3d) arg_error("div3d"); else arg_error("mul3d"); }
          is_released = false; ++position; continue;
        }

#endif // #ifdef gmic_float

        // Check for a custom command, and execute it, if found.
        if (std::strcmp("-input",command)) {
          const char *custom_command = 0, cc = *(command+1);
          bool custom_command_found = false, has_arguments = false;
          CImg<char> substituted_command;
          if ((cc>='a' && cc<='z') || (cc>='A' && cc<='Z') || cc=='_') {
            const int ind = gmic_hashcode(command+1,false);
            cimglist_for(commands_names[ind],l) {
              custom_command = commands_names[ind][l].data();
              const char *const command_code = commands[ind][l].data();
              if (!std::strcmp(command+1,custom_command)) {
                custom_command_found = true;
                if (is_debug) {
                  static char command_code_text[264];
                  const unsigned int ls = std::strlen(command_code);
                  if (ls>=264) {
                    std::memcpy(command_code_text,command_code,128);
                    std::memcpy(command_code_text+128," ... ",5);
                    std::memcpy(command_code_text+133,command_code+ls-130,131);
                  } else std::strcpy(command_code_text,command_code);
                  debug(images,"Found custom command '%s': '%s' (%s).",
                        custom_command,command_code_text,
                        commands_has_arguments[ind](l,0)?"takes arguments":"takes no arguments");
                }
                CImgList<char> arguments(32);
                // Set $0 to be the command name.
                CImg<char>::string(custom_command).move_to(arguments[0]);
                unsigned int nb_arguments = 0;

                if (commands_has_arguments[ind](l,0)) { // Command takes arguments.
                  gmic_substitute_args();

                  // Extract possible command arguments.
                  for (const char *ss = argument, *_ss = ss; _ss; ss =_ss+1)
                    if ((_ss=std::strchr(ss,','))!=0) {
                      if (ss==_ss) ++nb_arguments;
                      else {
                        if (++nb_arguments>=arguments.size())
                          arguments.insert(2+2*nb_arguments-arguments.size());
                        CImg<char> arg_item(ss,_ss-ss+1);
                        arg_item.back() = 0;
                        arg_item.move_to(arguments[nb_arguments]);
                      }
                    } else {
                      if (*ss) {
                        if (++nb_arguments>=arguments.size())
                          arguments.insert(1+nb_arguments-arguments.size());
                        if (*ss!=',') CImg<char>::string(ss).move_to(arguments[nb_arguments]);
                      }
                      break;
                    }

                  if (is_debug) {
                    debug(images,"Found %d given argument%s for command '%s'%s",
                          nb_arguments,nb_arguments!=1?"s":"",custom_command,nb_arguments>0?":":".");
                    for (unsigned int i = 1; i<=nb_arguments; ++i)
                      if (arguments[i]) debug(images,"  $%d = '%s'",i,arguments[i].data());
                      else debug(images,"  $%d = (undefined)",i);
                  }
                }

                // Substitute arguments in custom command expression.
                CImgList<char> substituted_items;
                CImg<char> inbraces;
                for (const char *nsource = command_code; *nsource;)
                  if (*nsource!='$') {
                    // If not starting with '$'.
                    const char *const nsource0 = nsource;
                    nsource = std::strchr(nsource0,'$');
                    if (!nsource) nsource = &commands[ind][l].back();
                    CImg<char>(nsource0,nsource-nsource0).move_to(substituted_items);
                  } else { // '$' expression found.
                    static CImg<char> substr(324);
                    inbraces.assign(1,1,1,1,0);
                    int ind = 0, ind1 = 0, l_inbraces = 0;
                    bool is_braces = false;
                    char sep = 0;

                    if (nsource[1]=='{') {
                      const char *const ptr_beg = nsource + 2, *ptr_end = ptr_beg;
                      unsigned int p = 0;
                      for (p = 1; p>0 && *ptr_end; ++ptr_end) {
                        if (*ptr_end=='{') ++p;
                        if (*ptr_end=='}') --p;
                      }
                      if (p) { CImg<char>(nsource++,1).move_to(substituted_items); continue; }
                      l_inbraces = ptr_end - ptr_beg - 1;
                      if (l_inbraces>0) inbraces.assign(ptr_beg,l_inbraces + 1).back() = 0;
                      is_braces = true;
                    }

                    // Substitute $? -> string describing image indices.
                    if (nsource[1]=='?') {
                      nsource+=2;
                      cimg_snprintf(substr,substr.width(),"%s",gmic_selection);
                      CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);

                      // Substitute $# -> maximum indice of known arguments.
                    } else if (nsource[1]=='#') {
                      nsource+=2;
                      cimg_snprintf(substr,substr.width(),"%u",nb_arguments);
                      CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
                      has_arguments = true;

                      // Substitute $* -> verbatim copy of the specified arguments string.
                    } else if (nsource[1]=='*') {
                      nsource+=2;
                      CImg<char>(argument,std::strlen(argument)).move_to(substituted_items);
                      has_arguments = true;

                      // Substitute $= -> transfer arguments to named variables.
                    } else if (nsource[1]=='=' &&
                               std::sscanf(nsource+2,"%255[a-zA-Z0-9_]",title)==1 &&
                               (*title<'0' || *title>'9')) {
                      nsource+=2+std::strlen(title);
                      for (unsigned int i=0; i<=nb_arguments; ++i) {
                        cimg_snprintf(substr,substr.width()," %s%u=\"",title,i);
                        CImg<char>(substr.data(),std::strlen(substr)).move_to(substituted_items);
                        CImg<char>(arguments[i].data(),arguments[i].width()-1).
                          move_to(substituted_items);
                        CImg<char>(2,1,1,1,'\"',' ').move_to(substituted_items);
                      }
                      has_arguments = true;

                      // Substitute $i and ${i} -> value of the i^th argument.
                    } else if ((std::sscanf(nsource,"$%d",&ind)==1 ||
                                (std::sscanf(nsource,"${%d%c",&ind,&sep)==2 && sep=='}'))) {
                      const int nind = ind + (ind<0?(int)nb_arguments+1:0);
                      if ((nind<=0 && ind) || nind>=arguments.width() || !arguments[nind]) {
                        error(custom_command,images,
                              "Command '%s': Undefined argument '$%d' (in expression '$%s%d%s'),"
                              " as %s%u argument%s given.",
                              custom_command,ind,sep=='}'?"{":"",ind,sep=='}'?"}":"",
                              nb_arguments?"only ":"",
                              nb_arguments,nb_arguments!=1?"s are":" is");
                      }
                      nsource+=cimg_snprintf(substr,substr.width(),"$%d",ind) + (sep=='}'?2:0);
                      if (arguments[nind].width()>1)
                        CImg<char>(arguments[nind].data(),arguments[nind].width()-1).
                          move_to(substituted_items);
                      if (nind!=0) has_arguments = true;

                      // Substitute ${i=$j} -> value of the i^th argument, or the default value,
                      // i.e. the value of another argument.
                    } else if (std::sscanf(nsource,"${%d=$%d%c",&ind,&ind1,&sep)==3 && sep=='}' &&
                               ind>0) {
                      const int nind1 = ind1 + (ind1<0?(int)nb_arguments+1:0);
                      if (nind1<=0 || nind1>=arguments.width() || !arguments[nind1])
                        error(custom_command,images,
                              "Command '%s': Undefined argument '$%d' (in expression '${%d=$%d}'),"
                              " as %s%u argument%s are given.",
                              custom_command,ind1,ind,ind1,
                              nb_arguments?"only ":"",
                              nb_arguments,nb_arguments!=1?"s are":" is");
                      nsource+=cimg_snprintf(substr,substr.width(),"${%d=$%d}",ind,ind1);
                      if (ind>=arguments.width()) arguments.insert(2+2*ind-arguments.size());
                      if (!arguments[ind]) {
                        arguments[ind] = arguments[nind1];
                        if (ind>(int)nb_arguments) nb_arguments = ind;
                      }
                      if (arguments[ind].width()>1)
                        CImg<char>(arguments[ind].data(),arguments[ind].width()-1).
                          move_to(substituted_items);
                      has_arguments = true;

                      // Substitute ${i=$#} -> value of the i^th argument, or the default value,
                      // i.e. the maximum indice of known arguments.
                    } else if (std::sscanf(nsource,"${%d=$#%c",&ind,&sep)==2 && sep=='}' &&
                               ind>0) {
                      if (ind>=arguments.width()) arguments.insert(2+2*ind-arguments.size());
                      if (!arguments[ind]) {
                        cimg_snprintf(substr,substr.width(),"%u",nb_arguments);
                        CImg<char>::string(substr).move_to(arguments[ind]);
                        if (ind>(int)nb_arguments) nb_arguments = ind;
                      }
                      nsource+=cimg_snprintf(substr,substr.width(),"${%d=$#}",ind);
                      if (arguments[ind].width()>1)
                        CImg<char>(arguments[ind].data(),arguments[ind].width()-1).
                          move_to(substituted_items);
                      has_arguments = true;

                      // Substitute ${i=default} -> value of the i^th argument,
                      // or the specified default value.
                    } else if (std::sscanf(inbraces,"%d%c",&ind,&sep)==2 && sep=='=' &&
                               ind>0) {
                      nsource+=l_inbraces + 3;
                      if (ind>=arguments.width()) arguments.insert(2+2*ind-arguments.size());
                      if (!arguments[ind]) {
                        CImg<char>::string(inbraces.data() +
                                           cimg_snprintf(substr,substr.width(),"%d=",ind)).
                          move_to(arguments[ind]);
                        if (ind>(int)nb_arguments) nb_arguments = ind;
                      }
                      if (arguments[ind].width()>1)
                        CImg<char>(arguments[ind].data(),arguments[ind].width()-1).
                          move_to(substituted_items);
                      has_arguments = true;

                      // Substitute any other expression starting by '$'.
                    } else {

                      // Substitute ${subset} -> values of the selected subset of arguments,
                      // separated by ','.
                      if (is_braces) {
                        if ((*inbraces>='a' && *inbraces<='z') ||
                            (*inbraces>='A' && *inbraces<='Z') ||
                            *inbraces=='_') {
                          CImg<char>(nsource++,1).move_to(substituted_items);
                        } else if (*inbraces) {
                          CImg<unsigned int> inds;
                          const int _verbosity = verbosity;
                          const bool _is_debug = is_debug;
                          bool is_valid_subset = true;
                          verbosity = -16384; is_debug = false;
                          try {
                            inds = selection2cimg(inbraces,nb_arguments+1,
                                                  CImgList<char>::empty(),"",false,
                                                  false,CImg<char>::empty());
                          } catch (...) { inds.assign(); is_valid_subset = false; }
                          verbosity = _verbosity; is_debug = _is_debug;
                          if (is_valid_subset) {
                            nsource+=l_inbraces + 3;
                            if (inds) {
                              cimg_forY(inds,j) {
                                const unsigned int ind = inds[j];
                                if (ind) has_arguments = true;
                                if (!arguments[ind])
                                  error(custom_command,images,
                                        "Command '%s': Undefined argument '$%d' "
                                        "(in expression '${%s}').",
                                        custom_command,ind,inbraces.data());
                                substituted_items.insert(arguments[ind]);
                                substituted_items.back().back() = ',';
                              }
                              if (substituted_items.back().width()>1)
                                --(substituted_items.back()._width);
                              else substituted_items.remove();
                              has_arguments = true;
                            }
                          } else CImg<char>(nsource++,1).move_to(substituted_items);
                        } else nsource+=3; // Substitute '${}' by ''.
                      } else CImg<char>(nsource++,1).move_to(substituted_items);
                    }
                  }
                CImg<char>::vector(0).move_to(substituted_items);
                (substituted_items>'x').move_to(substituted_command);

                // Substitute special character codes appearing outside strings.
                bool is_dquoted = false;
                for (char *s = substituted_command.data(); *s; ++s) {
                  const char c = *s;
                  if (c=='\"') is_dquoted = !is_dquoted;
                  if (!is_dquoted) *s = c<' '?(c==_dollar?'$':c==_lbrace?'{':c==_rbrace?'}':
                                               c==_comma?',':c==_dquote?'\"':c==_arobace?'@':c):c;
                }

                if (is_debug) {
                  static char command_code_text[264];
                  const unsigned int l = std::strlen(substituted_command.data());
                  if (l>=264) {
                    std::memcpy(command_code_text,substituted_command.data(),128);
                    std::memcpy(command_code_text+128," ... ",5);
                    std::memcpy(command_code_text+133,substituted_command.data()+l-130,131);
                  } else std::strcpy(command_code_text,substituted_command.data());
                  debug(images,"Expand command line for command '%s' to: '%s'.",
                        custom_command,command_code_text);
                }
                break;
              }
            }
          }

          if (custom_command_found) {
            const CImgList<char>
              ncommands_line = commands_line_to_CImgList(substituted_command.data());
            unsigned int nvariables_sizes[256];
            for (unsigned int l = 0; l<256; ++l) nvariables_sizes[l] = variables[l].size();
            CImgList<char> nimages_names(selection.height());
            CImgList<T> nimages(selection.height());
            unsigned int nposition = 0;
            CImg<char>::string(custom_command).move_to(scope);
            if (is_get_version) {
              cimg_forY(selection,l) {
                nimages[l] = images[selection[l]];
                nimages_names[l] = images_names[selection[l]];
              }
              parse(ncommands_line,nposition,nimages,nimages_names,nvariables_sizes);
              nimages.move_to(images,~0U);
              cimglist_for(nimages_names,l) nimages_names[l].copymark();
              nimages_names.move_to(images_names,~0U);
            } else {
              cimg_forY(selection,l) {
                if (images[selection[l]].is_shared())
                  nimages[l] = CImg<T>(images[selection[l]],true);
                else nimages[l].swap(images[selection[l]]);
                nimages_names[l].swap(images_names[selection[l]]);
              }
              parse(ncommands_line,nposition,nimages,nimages_names,nvariables_sizes);
              const unsigned int nb = cimg::min((unsigned int)selection.height(),nimages.size());
              if (nb>0) {
                for (unsigned int i = 0; i<nb; ++i) {
                  if (images[selection[i]].is_shared()) {
                    images[selection[i]] = nimages[i];
                    nimages[i].assign();
                  } else images[selection[i]].swap(nimages[i]);
                  images_names[selection[i]].swap(nimages_names[i]);
                }
                nimages.remove(0,nb-1);
                nimages_names.remove(0,nb-1);
              }
              if (nb<(unsigned int)selection.height())
                remove_images(images,images_names,selection,nb,selection.height()-1);
              else if (nimages) {
                const unsigned int ind0 = selection?selection.back()+1:images.size();
                nimages_names.move_to(images_names,ind0);
                nimages.move_to(images,ind0);
              }
            }
            for (unsigned int l = 0; l<255; ++l) if (variables[l].size()>nvariables_sizes[l]) {
                variables_names[l].remove(nvariables_sizes[l],variables[l].size()-1);
                variables[l].remove(nvariables_sizes[l],variables[l].size()-1);
              }
            scope.remove();
            is_return = false;
            if (has_arguments) ++position;
            continue;
          }
        }
      }  // if (*item=='-') {

      // Variable assignment.
      char sep = 0;
      if (std::strchr(item,'=') && std::sscanf(item,"%255[a-zA-Z0-9_]%c",title,&sep)==2 &&
          sep=='=' && (*title<'0' || *title>'9')) {
        CImg<char>
          name(title,std::strlen(title)+1),
          value = CImg<char>::string(item+name.width());
        int ind = 0; bool is_name_found = false;
        const unsigned int sind = gmic_hashcode(name,true);
        const int lind = *name=='_'?0:variables_sizes[sind];
        CImgList<char>
          &_variables = variables[sind],
          &_variables_names = variables_names[sind];
        for (int l = _variables.size()-1; l>=lind; --l)
          if (!std::strcmp(_variables_names[l],name)) {
            is_name_found = true; ind = l; break;
          }
        print(images,"Set %s variable %s='%s'.",
              *name=='_'?"global":"local",
              name.data(),value.data());
        if (is_name_found) value.move_to(_variables[ind]);
        else { name.move_to(_variables_names); value.move_to(_variables); }
        continue;
      }

      // Input.
      if (!std::strcmp("-input",command)) ++position;
      else { std::strcpy(command,"-input"); argument = item; *restriction = 0; }
      gmic_substitute_args();
      if (!is_restriction || !selection) selection.assign(1,1,1,1,images.size());
      static char indicesy[256], indicesz[256], indicesc[256];
      float dx = 0, dy = 1, dz = 1, dc = 1, nb = 1;
      char sepx = 0, sepy = 0, sepz = 0, sepc = 0;
      CImg<unsigned int> indx, indy, indz, indc;
      CImgList<char> input_images_names;
      CImgList<T> input_images;
      *indices = *argx = *argy = *argz = *argc = 0;

      CImg<char> arg_input(argument,std::strlen(argument)+1);
      gmic_strreplace(arg_input);

      if (*arg_input=='0' && !arg_input[1]) {

        // Empty image.
        print(images,"Input empty image at position%s",
              gmic_selection);
        input_images.assign(1);
        CImg<char>::string("[empty]").move_to(input_images_names);


      } else if ((std::sscanf(arg_input,"[%255[a-zA-Z_0-9%.eE%^,:+-]%c%c",indices,&sep,&end)==2 &&
                  sep==']') ||
                 std::sscanf(arg_input,"[%255[a-zA-Z_0-9%.eE%^,:+-]]x%f%c",indices,&nb,&end)==2) {

        // Nb copies of existing images.
        nb = cimg::round(nb);
        const CImg<unsigned int> inds = selection2cimg(indices,images.size(),images_names,
                                                       "-input",true,false,CImg<char>::empty());
        static char st_tmp[256];
        std::strncpy(st_tmp,selection2string(inds,images_names,true),sizeof(st_tmp)-1);
        st_tmp[sizeof(st_tmp)-1] = 0;
        if (nb<=0) arg_error("input");
        if (nb!=1)
          print(images,"Input %u copies of image%s at position%s",
                (unsigned int)nb,
                st_tmp,
                gmic_selection);
        else
          print(images,"Input copy of image%s at position%s",
                st_tmp,
                gmic_selection);
        for (unsigned int i = 0; i<(unsigned int)nb; ++i) cimg_foroff(inds,l) {
          input_images.insert(images[inds[l]]);
          input_images_names.insert(images_names[inds[l]].get_copymark());
        }
      } else if ((sep=0,true) &&
                 (std::sscanf(arg_input,"%255[][a-zA-Z0-9_.eE%+-]%c",
                              argx,&end)==1 ||
                  std::sscanf(arg_input,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                              argx,argy,&end)==2 ||
                  std::sscanf(arg_input,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                              "%255[][a-zA-Z0-9_.eE%+-]%c",
                              argx,argy,argz,&end)==3 ||
                  std::sscanf(arg_input,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                              "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-]%c",
                              argx,argy,argz,argc,&end)==4 ||
                  std::sscanf(arg_input,"%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],"
                              "%255[][a-zA-Z0-9_.eE%+-],%255[][a-zA-Z0-9_.eE%+-],%c",
                              argx,argy,argz,argc,&sep)==5) &&
                 ((std::sscanf(argx,"[%255[a-zA-Z0-9_.%+-]%c%c",indices,&sepx,&end)==2 &&
                   sepx==']' &&
                   (indx=selection2cimg(indices,images.size(),images_names,"-input",true,
                                        false,CImg<char>::empty())).height()==1) ||
                  (std::sscanf(argx,"%f%c",&dx,&end)==1 && dx>=1) ||
                  (std::sscanf(argx,"%f%c%c",&dx,&sepx,&end)==2 && dx>0 && sepx=='%')) &&
                 (!*argy ||
                  (std::sscanf(argy,"[%255[a-zA-Z0-9_.%+-]%c%c",indicesy,&sepy,&end)==2 &&
                   sepy==']' &&
                   (indy=selection2cimg(indicesy,images.size(),images_names,"-input",true,
                                        false,CImg<char>::empty())).height()==1) ||
                  (std::sscanf(argy,"%f%c",&dy,&end)==1 && dy>=1) ||
                  (std::sscanf(argy,"%f%c%c",&dy,&sepy,&end)==2 && dy>0 && sepy=='%')) &&
                 (!*argz ||
                  (std::sscanf(argz,"[%255[a-zA-Z0-9_.%+-]%c%c",indicesz,&sepz,&end)==2 &&
                   sepz==']' &&
                   (indz=selection2cimg(indicesz,images.size(),images_names,"-input",true,
                                        false,CImg<char>::empty())).height()==1) ||
                  (std::sscanf(argz,"%f%c",&dz,&end)==1 && dz>=1) ||
                  (std::sscanf(argz,"%f%c%c",&dz,&sepz,&end)==2 && dz>0 && sepz=='%')) &&
                 (!*argc ||
                  (std::sscanf(argc,"[%255[a-zA-Z0-9_.%+-]%c%c",indicesc,&sepc,&end)==2 &&
                   sepc==']' &&
                   (indc=selection2cimg(indicesc,images.size(),images_names,"-input",true,
                                        false,CImg<char>::empty())).height()==1) ||
                  (std::sscanf(argc,"%f%c",&dc,&end)==1 && dc>=1) ||
                  (std::sscanf(argc,"%f%c%c",&dc,&sepc,&end)==2 && dc>0 && sepc=='%'))) {

        // New image with specified dimensions and optionally values.
        if (indx) { dx = (float)images[*indx].width(); sepx = 0; }
        if (indy) { dy = (float)images[*indy].height(); sepy = 0; }
        if (indz) { dz = (float)images[*indz].depth(); sepz = 0; }
        if (indc) { dc = (float)images[*indc].spectrum(); sepc = 0; }
        int idx = 0, idy = 0, idz = 0, idc = 0;
        const CImg<T> &img = images.size()?images.back():CImg<T>::empty();
        if (sepx=='%') { idx = (int)cimg::round(dx*img.width()/100); if (!idx) ++idx; }
        else idx = (int)cimg::round(dx);
        if (sepy=='%') { idy = (int)cimg::round(dy*img.height()/100); if (!idy) ++idy; }
        else idy = (int)cimg::round(dy);
        if (sepz=='%') { idz = (int)cimg::round(dz*img.depth()/100); if (!idz) ++idz; }
        else idz = (int)cimg::round(dz);
        if (sepc=='%') { idc = (int)cimg::round(dc*img.spectrum()/100); if (!idc) ++idc; }
        else idc = (int)cimg::round(dc);
        if (idx<=0 || idy<=0 || idz<=0 || idc<=0) arg_error("input");
        CImg<char> st_values;
        if (sep) {
          const char *_st_values = arg_input.data() + std::strlen(argx) + std::strlen(argy) +
            std::strlen(argz) + std::strlen(argc) + 4;
          st_values.assign(_st_values,std::strlen(_st_values)+1);
          cimg::strpare(st_values,'\'',true,false);
          gmic_strreplace(st_values);
          static char st_values_text[72];
          const unsigned int l = std::strlen(st_values);
          if (l>=72) {
            std::memcpy(st_values_text,st_values.data(),32);
            std::memcpy(st_values_text+32," ... ",5);
            std::memcpy(st_values_text+37,st_values.data()+l-34,35);  // Last '\0' is included.
          } else std::strcpy(st_values_text,st_values);
          print(images,"Input image at position%s, with values '%s'",
                gmic_selection,st_values_text);
        } else
          print(images,"Input black image at position%s",
                gmic_selection);
        CImg<T> new_image(idx,idy,idz,idc,0);
        if (st_values) {
          new_image.fill(st_values.data(),true);
          cimg_snprintf(title,sizeof(title),"[image of '%s']",st_values.data());
          gmic_ellipsize(title,sizeof(title));
          CImg<char>::string(title).move_to(input_images_names);
        } else CImg<char>::string("[unnamed]").move_to(input_images_names);
        new_image.move_to(input_images);

      } else if (*arg_input=='(' && arg_input[std::strlen(arg_input)-1]==')') {

        // New IxJxKxL image specified as array.
        unsigned int cx = 0, cy = 0, cz = 0, cc = 0, maxcx = 0, maxcy = 0, maxcz = 0;
        const char *nargument = 0;
        for (nargument = arg_input.data() + 1; *nargument; ) {
          static char s_value[256];
          *s_value = 0;
          char separator = 0;
          double value = 0;
          if (std::sscanf(nargument,"%255[0-9.eE+-]%c",s_value,&separator)==2 &&
              std::sscanf(s_value,"%lf%c",&value,&end)==1) {
            if (cx>maxcx) maxcx = cx;
            if (cy>maxcy) maxcy = cy;
            if (cz>maxcz) maxcz = cz;
            switch (separator) {
            case '^' : cx = cy = cz = 0; ++cc; break;
            case '/' : cx = cy = 0; ++cz; break;
            case ';' : cx = 0; ++cy; break;
            case ',' : ++cx; break;
            case ')' : break;
            default : arg_error("input");
            }
            nargument+=std::strlen(s_value) + 1;
          } else break;
        }
        if (*nargument) arg_error("input");
        CImg<T> img(maxcx+1,maxcy+1,maxcz+1,cc+1,0);
        cx = cy = cz = cc = 0;
        for (nargument = arg_input.data() + 1; *nargument; ) {
          static char s_value[256];
          *s_value = 0;
          char separator = 0;
          double value = 0;
          if (std::sscanf(nargument,"%255[0-9.eE+-]%c",s_value,&separator)==2 &&
              std::sscanf(s_value,"%lf%c",&value,&end)==1) {
            img(cx,cy,cz,cc) = (T)value;
            switch (separator) {
            case '^' : cx = cy = cz = 0; ++cc; break;
            case '/' : cx = cy = 0; ++cz; break;
            case ';' : cx = 0; ++cy; break;
            default : ++cx;
            }
            nargument+=std::strlen(s_value) + (separator?1:0);
          } else break;
        }
        print(images,"Input image at position%s, with values '%s'",
              gmic_selection,
              argument_text);
        img.move_to(input_images);
        arg_input.move_to(input_images_names);

      } else {

        // Input filename.
        static char cext[8], _filename[4096], filename_tmp[512] = { 0 }, options[256];
        *cext = *_filename = *filename_tmp = *options = 0;
        bool is_network_file = false;
        if (std::sscanf(argument,"%8[a-zA-Z]:%4095[^,],%255s",cext,_filename,options)<2 ||
            !cext[1] || // length of 'ext' must be >=2 (avoid case 'C:\\..' on Windows).
            !cimg::strcasecmp(cext,"http") || !cimg::strcasecmp(cext,"https")) {
          *cext = *_filename = *options = 0;
          if (std::sscanf(argument,"%4095[^,],%255s",_filename,options)!=2) {
            std::strncpy(_filename,argument,sizeof(_filename)-1);
            _filename[sizeof(_filename)-1] = 0;
          }
        }
        gmic_strreplace(_filename);
        gmic_strreplace(options);
        CImg<char> __filename0 = CImg<char>::string(_filename);
        const char *const _filename0 = __filename0.data();

        // Test for network file requests.
        if (!cimg::strncasecmp(_filename,"http://",7) ||
            !cimg::strncasecmp(_filename,"https://",8)) {
          cimg::load_network_external(_filename,filename_tmp);
          std::strncpy(_filename,filename_tmp,sizeof(_filename)-1);
          _filename[sizeof(_filename)-1] = 0;
          *filename_tmp = 0;
          is_network_file = true;
        }

        if (*cext) { // Force output to be read as a '.ext' file : generate random filename.
          if (*_filename=='-' && (!_filename[1] || _filename[1]=='.')) {
            // Simplify filename 'ext:-.foo' as '-.ext'.
            cimg_snprintf(_filename,sizeof(_filename),"-.%s",cext);
            *cext = 0;
          } else {
            std::FILE *file = 0;
            do {
              cimg_snprintf(filename_tmp,sizeof(filename_tmp),"%s%c%s.%s",
                            cimg::temporary_path(),cimg_file_separator,
                            cimg::filenamerand(),cext);
              if ((file=std::fopen(filename_tmp,"rb"))!=0) std::fclose(file);
            } while (file);

            // Make a temporary copy (or link) of the original file.
#if cimg_OS==1
            const char *const _filename_path = realpath(_filename,0);
            if (symlink(_filename_path,filename_tmp))
              CImg<unsigned char>::get_load_raw(_filename).save_raw(filename_tmp);
            std::free((void*)_filename_path);
#else // #if cimg_OS==1
            CImg<unsigned char>::get_load_raw(_filename).save_raw(filename_tmp);
#endif // #if cimg_OS==1
          }
        }

        const char
          *const filename = *filename_tmp?filename_tmp:_filename,
          *const ext = cimg::split_filename(filename);

        if (!cimg::strcasecmp("off",ext)) {

          // 3d object .off file.
          print(images,"Input 3d object '%s' at position%s",
                _filename0,
                gmic_selection);
          CImgList<unsigned int> primitives;
          CImgList<float> colors;
          CImg<float> vertices = CImg<float>::get_load_off(primitives,colors,filename);
          const CImg<float> opacities(1,primitives.size(),1,1,1);
          vertices.object3dtoCImg3d(primitives,colors,opacities).move_to(input_images);
          input_images_names.insert(__filename0);
        } else if (!cimg::strcasecmp(ext,"avi") ||
                   !cimg::strcasecmp(ext,"mov") ||
                   !cimg::strcasecmp(ext,"asf") ||
                   !cimg::strcasecmp(ext,"divx") ||
                   !cimg::strcasecmp(ext,"flv") ||
                   !cimg::strcasecmp(ext,"mpg") ||
                   !cimg::strcasecmp(ext,"m1v") ||
                   !cimg::strcasecmp(ext,"m2v") ||
                   !cimg::strcasecmp(ext,"m4v") ||
                   !cimg::strcasecmp(ext,"mjp") ||
                   !cimg::strcasecmp(ext,"mkv") ||
                   !cimg::strcasecmp(ext,"mpe") ||
                   !cimg::strcasecmp(ext,"movie") ||
                   !cimg::strcasecmp(ext,"ogm") ||
                   !cimg::strcasecmp(ext,"ogg") ||
                   !cimg::strcasecmp(ext,"qt") ||
                   !cimg::strcasecmp(ext,"rm") ||
                   !cimg::strcasecmp(ext,"vob") ||
                   !cimg::strcasecmp(ext,"wmv") ||
                   !cimg::strcasecmp(ext,"xvid") ||
                   !cimg::strcasecmp(ext,"mpeg")) {

          // Image sequence file.
          unsigned int value0 = 0, value1 = 0, step = 1;
          float _value0 = 0, _value1 = 0;
          char sep0 = 0, sep1 = 0;
          if ((std::sscanf(options,"%f%c,%f%c,%u%c",&_value0,&sep0,&_value1,&sep1,&step,&end)==5 &&
               sep0=='%' && sep1=='%') ||
              (std::sscanf(options,"%f%c,%f,%u%c",&_value0,&sep0,&_value1,&step,&end)==4 &&
               sep0=='%') ||
              (std::sscanf(options,"%f,%f%c,%u%c",&_value0,&_value1,&sep1,&step,&end)==4 &&
               sep1=='%') ||
              std::sscanf(options,"%f,%f,%u%c",&_value0,&_value1,&step,&end)==3 ||
              (std::sscanf(options,"%f%c,%f%c%c",&_value0,&sep0,&_value1,&sep1,&end)==4 &&
               sep0=='%' && sep1=='%') ||
              (std::sscanf(options,"%f%c,%f%c",&_value0,&sep0,&_value1,&end)==3 &&
               sep0=='%') ||
              (std::sscanf(options,"%f,%f%c%c",&_value0,&_value1,&sep1,&end)==3 &&
               sep1=='%') ||
              std::sscanf(options,"%f,%f%c",&_value0,&_value1,&end)==2) { // Read several frames
            print(images,"Input frames %g%s..%g%s with step %u of file '%s' at position%s",
                  _value0,sep0=='%'?"%":"",
                  _value1,sep1=='%'?"%":"",
                  step,
                  _filename0,
                  gmic_selection);
            if (sep0=='%' || sep1=='%') {
              const unsigned int
                nb_frames = CImg<unsigned int>::get_load_ffmpeg(filename,0,0,0)[0];
              value0 = (unsigned int)cimg::round(sep0=='%'?_value0*nb_frames/100:_value0);
              value1 = (unsigned int)cimg::round(sep1=='%'?_value1*nb_frames/100:_value1);
            }
          } else if ((std::sscanf(options,"%f%c%c",&_value0,&sep0,&end)==2 && sep0=='%') ||
                     std::sscanf(options,"%f%c",&_value0,&end)==1) { // Read one frame
            print(images,"Input frame %g%s of file '%s' at position%s",
                  _value0,sep0=='%'?"%":"",
                  _filename0,
                  gmic_selection);
            if (sep0=='%') {
              const unsigned int
                nb_frames = CImg<unsigned int>::get_load_ffmpeg(filename,0,0,0)[0];
              value0 = (unsigned int)cimg::round(_value0*nb_frames/100);
            }
            value1 = value0; step = 1;
          } else { // Read all frames
            print(images,"Input all frames of file '%s' at position%s",
                  _filename0,
                  gmic_selection);
            value0 = 0; value1 = ~0U; sep0 = sep1 = 0; step = 1;
          }
          input_images.load_ffmpeg(filename,value0,value1,step);
          if (input_images) {
            input_images_names.insert(__filename0);
            if (input_images.size()>1)
              input_images_names.insert(input_images.size()-1,__filename0.copymark());
          }
        } else if (!cimg::strcasecmp("raw",ext)) {

          // Raw file.
          float dx = 0, dy = 1, dz = 1, dc = 1;
          *argx = 0;
          if (!*options ||
              std::sscanf(options,"%f%c",&dx,&end)==1 ||
              std::sscanf(options,"%f,%f%c",&dx,&dy,&end)==2 ||
              std::sscanf(options,"%f,%f,%f%c",&dx,&dy,&dz,&end)==3 ||
              std::sscanf(options,"%f,%f,%f,%f%c",&dx,&dy,&dz,&dc,&end)==4 ||
              std::sscanf(options,"%255[a-zA-Z]%c",argx,&end)==1 ||
              std::sscanf(options,"%255[a-zA-Z],%f%c",argx,&dx,&end)==2 ||
              std::sscanf(options,"%255[a-zA-Z],%f,%f%c",argx,&dx,&dy,&end)==3 ||
              std::sscanf(options,"%255[a-zA-Z],%f,%f,%f%c",argx,&dx,&dy,&dz,&end)==4 ||
              std::sscanf(options,"%255[a-zA-Z],%f,%f,%f,%f%c",argx,&dx,&dy,&dz,&dc,&end)==5) {
            const char *const stype = *argx?argx:cimg::type<T>::string();
            dx = cimg::round(dx);
            dy = cimg::round(dy);
            dz = cimg::round(dz);
            dc = cimg::round(dc);
            if (dx<0 || dy<=0 || dz<=0 || dc<=0)
              error(images,"Command 'input': raw file '%s', invalid specified "
                    "dimensions %gx%gx%gx%g.",
                    _filename0,dx,dy,dz,dc);
            print(images,"Input raw file '%s' with type '%s' at position%s",
                  _filename0,stype,
                  gmic_selection);

#define gmic_load_raw(value_type,svalue_type) \
            if (!strcasecmp(stype,svalue_type)) \
              CImg<value_type>::get_load_raw(filename,(unsigned int)dx,(unsigned int)dy,\
                                             (unsigned int)dz,(unsigned int)dc).\
                move_to(input_images);
            gmic_load_raw(bool,"bool")
            else gmic_load_raw(unsigned char,"uchar")
              else gmic_load_raw(unsigned char,"unsigned char")
                else gmic_load_raw(char,"char")
                  else gmic_load_raw(unsigned short,"ushort")
                    else gmic_load_raw(unsigned short,"unsigned short")
                      else gmic_load_raw(short,"short")
                        else gmic_load_raw(unsigned int,"uint")
                          else gmic_load_raw(unsigned int,"unsigned int")
                            else gmic_load_raw(int,"int")
                              else gmic_load_raw(float,"float")
                                else gmic_load_raw(double,"double")
                                  else error(images,"Command 'input': raw file '%s', "
                                             "invalid specified pixel type '%s'.\n",
                                             _filename0,stype);
            input_images_names.insert(__filename0);
          } else
            error(images,"Command 'input': raw file '%s', invalid file options '%s'.",
                  _filename0,options);
        } else if (!cimg::strcasecmp("yuv",ext)) {

          // YUV file.
          float first = 0, last = ~0U, step = 1, dx = 0, dy = 0;
          if (std::sscanf(options,"%f,%f,%f,%f,%f",&dx,&dy,&first,&last,&step)>0) {
            first = cimg::round(first);
            last = cimg::round(last);
            step = cimg::round(step);
            dx = cimg::round(dx);
            dy = cimg::round(dy);
            if (dx<=0 || dy<=0)
              error(images,"Command 'input': YUV file '%s', invalid specified dimensions %gx%g.",
                    _filename0,dx,dy);
            print(images,"Input YUV file '%s' at position%s",
                  _filename0,
                  gmic_selection);
            input_images.load_yuv(filename,(unsigned int)dx,(unsigned int)dy,
                                  (unsigned int)first,(unsigned int)last,(unsigned int)step);

            input_images_names.insert(__filename0);
            if (input_images.size()>1)
              input_images_names.insert(input_images.size()-1,__filename0.copymark());
          } else
            error(images,"Command 'input': YUV file '%s', invalid file options '%s'.",
                  _filename0,options);
        } else if (!cimg::strcasecmp("gmic",ext)) {

          // G'MIC custom commands file
          print(images,"Input custom commands file '%s'",
                _filename0);
          unsigned int siz = 0;
          for (unsigned int l = 0; l<256; ++l) siz+=commands[l].size();
          std::FILE *const file = cimg::fopen(filename,"rb");
          add_commands(file,commands_names,commands,commands_has_arguments);
          cimg::fclose(file);
          if (verbosity>=0 || is_debug) {
            unsigned int nb_added = 0;
            for (unsigned int l = 0; l<256; ++l) nb_added+=commands[l].size();
            nb_added-=siz;
            std::fprintf(cimg::output()," (added %u command%s, total %u).",
                         nb_added,nb_added>1?"s":"",siz+nb_added);
            std::fflush(cimg::output());
          }
          continue;
        } else {

          // Other file types.
          print(images,"Input file '%s' at position%s",
                _filename0,
                gmic_selection);
          try { input_images.load(filename); }
          catch (CImgException&) {
            std::FILE *file = 0;
            if (!(file=std::fopen(filename,"r"))) {
              if (cimg::type<T>::string()==cimg::type<float>::string() || *ext || *filename!='-') {
                if (*filename=='-' && filename[1]) { // Check for command misspelling.
                  const char *native_commands_names[] = {
                    "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s",
                    "t","u","v","w","x","y","z",
                    "+","-","*","/",">","<","%","^","=","sh","mv","rm","rv","<<",">>","==",">=",
                    "<=","//","**","!=",
                    "d3d","+3d","b3d","/3d","f3d","l3d","m3d","*3d","o3d","p3d","r3d","s3d","-3d",
                    "t3d","db3d","md3d","rv3d","sl3d","ss3d","div3d",
                    "append","autocrop","add","add3d","abs","and","atan2","acos","asin","atan",
                    "axes",
                    "blur","bsr","bsl","bilateral","background3d","break",
                    "check","crop","channels","columns","command","camera","cut","cos","convolve",
                    "correlate","color3d","col3d","cosh","continue",
                    "done","do","debug","divide","distance","dilate","double3d","denoise","deriche",
                    "dijkstra","displacement","display","display3d",
                    "endif","else","elif","endlocal","endl","echo","exec","error","endian","exp",
                    "eq","ellipse","equalize","erode","elevation3d","eigen","eikonal",
                    "fill","flood","focale3d","fft",
                    "ge","gt","gradient","graph",
                    "histogram","hsi2rgb","hsl2rgb","hsv2rgb","hessian","haar",
                    "input","if","image","index","invert","isoline3d","isosurface3d","inpaint",
                    "ifft","ihaar",
                    "keep",
                    "local","le","lt","log","log2","log10","line","lab2rgb","label","light3d",
                    "move","mirror","mul","mod","max","min","mmul","mode3d","moded3d","map",
                    "median","mdiv","mse","mandelbrot","mul3d"
                    "name","normalize","neq","noise",
                    "output","onfail","object3d","or","opacity3d",
                    "permute","progress","print","pow","point","polygon","plasma","pose3d",
                    "primitives3d","plot",
                    "quiver","quit",
                    "remove","repeat","resize","reverse","return","rows","rotate","resize2x",
                    "resize3x","round","rand","rotate3d","rgb2hsi","rgb2hsl","rgb2hsv","rgb2lab",
                    "rgb2srgb","rol","ror","reverse3d",
                    "status","skip","set","split","shared","shift","slices","srand","sub","sqrt",
                    "sqr","sign","sin","sort","solve","sub3d","spline","sharpen","smooth","split3d",
                    "svd","sphere3d","specl3d","specs3d","sinc","sinh","srgb2rgb","streamline3d",
                    "structuretensors","select",
                    "type","threshold","tan","text","texturize3d","trisolve","tanh",
                    "unroll","uncommand",
                    "vanvliet","verbose",
                    "while","warning","window","warp","watershed","wait",
                    "xor",0
                  };
                  const char *misspelled = 0;
                  int dmin = 4;
                  for (unsigned int l = 0; native_commands_names[l]; ++l) {
                    // Look in native commands.
                    const char *const c = native_commands_names[l];
                    const int d = gmic_levenshtein(c,filename+1);
                    if (d<dmin) { dmin = d; misspelled = native_commands_names[l]; }
                  }
                  for (unsigned int i = 0; i<256; ++i)
                    // Look in custom commands.
                    cimglist_for(commands_names[i],l) {
                      const char *const c = commands_names[i][l].data();
                      const int d = gmic_levenshtein(c,filename+1);
                      if (d<dmin) { dmin = d; misspelled = commands_names[i][l].data(); }
                    }
                  if (misspelled)
                    error(images,"Unknown command or filename '%s' (did you mean '-%s' ?).",
                          argument_text,misspelled);
                  else error(images,"Unknown command or filename '%s'.",
                             argument_text);
                } else error(images,"Unknown %s '%s'.",
                             *filename=='-'?"command or filename":"filename",
                             argument_text);
              } else
                error(images,"Unknown command '%s' in '%s' type mode "
                      "(command defined only in 'float' type mode ?).",
                      argument_text,cimg::type<T>::string());
            } else throw;
          }
          input_images_names.insert(__filename0);
          if (input_images.size()>1)
            input_images_names.insert(input_images.size()-1,__filename0.copymark());
        }

        if (*filename_tmp) std::remove(filename_tmp);  // Clean temporary file if used.
        if (is_network_file) std::remove(_filename);   // Clean temporary file if network input.
      }

      if (verbosity>=0 || is_debug) {
        if (input_images) {
          const unsigned int last = input_images.size() - 1;
          if (input_images.size()==1) {
            if (input_images[0].is_CImg3d(true))
              std::fprintf(cimg::output()," (%u vertices, %u primitives).",
                           cimg::float2uint(input_images(0,6)),
                           cimg::float2uint(input_images(0,7)));
            else
              std::fprintf(cimg::output()," (1 image %dx%dx%dx%d).",
                           input_images[0].width(),input_images[0].height(),
                           input_images[0].depth(),input_images[0].spectrum());
          } else
            std::fprintf(cimg::output()," (%u images [0] = %dx%dx%dx%d, %s[%u] = %dx%dx%dx%d).",
                         input_images.size(),
                         input_images[0].width(),input_images[0].height(),
                         input_images[0].depth(),input_images[0].spectrum(),
                         last==1?"":"..,",last,
                         input_images[last].width(),input_images[last].height(),
                         input_images[last].depth(),input_images[last].spectrum());
        } else {
          std::fprintf(cimg::output()," (no available data).");
          input_images_names.assign();
        }
        std::fflush(cimg::output());
      }

      for (unsigned int l = 0, siz = selection.height()-1U, off = 0; l<=siz; ++l) {
        const unsigned int ind = selection[l] + off;
        off+=input_images.size();
        if (l!=siz) {
          images.insert(input_images,ind);
          images_names.insert(input_images_names,ind);
        } else {
          input_images.move_to(images,ind);
          input_images_names.move_to(images_names,ind);
        }
      }

      if (new_name) new_name.move_to(images_names[selection[0]]);
      is_released = false;
    }

    // Post-check global environment consistency.
    if (images_names.size()!=images.size())
      error(images,"Internal error: Images (%u) and images names (%u) have different size, "
            "at return point.",
            images_names.size(),images.size());
    if (!scope)
      error(images,"Internal error: Scope is empty, at return point.");

    // Post-check local environment consistency.
    if (!is_quit && !is_return) {
      const CImg<char> &s = scope.back();
      if (s[0]=='*' && (s[1]=='d' || s[1]=='i' || s[1]=='r' || (s[1]=='l' && !is_endlocal)))
        error(images,"A '%s' command is missing, at return point.",
              s[1]=='d'?"while":s[1]=='i'?"endif":s[1]=='r'?"done":"endlocal");
    } else if (initial_scope_size<scope.size()) scope.remove(initial_scope_size,scope.size()-1);

    // Display result, if not 'released' before.
#if defined(gmic_float) && cimg_display!=0

    if (!is_released && scope.size()==1 && images) {
      CImgList<unsigned int> lselection, lselection3d;
      bool is_first3d = false;
      cimglist_for(images,l) {
        const bool is_3d = images[l].is_CImg3d(true);
        if (!l) is_first3d = is_3d;
        CImg<unsigned int>::vector(l).move_to(is_3d?lselection3d:lselection);
      }
      if (is_first3d) {
        display_objects3d(images,images_names,lselection3d>'y');
        if (lselection) display_images(images,images_names,lselection>'y',0);
      } else {
        if (lselection) display_images(images,images_names,lselection>'y',0);
        if (lselection3d) display_objects3d(images,images_names,lselection3d>'y');
      }
      is_released = true;
    }

#endif // #if defined(gmic_float) && cimg_display!=0

    if (is_debug) debug(images,"%sEnd G'MIC parser in scope '%s/' [%s].%s\n",
                        cimg::t_bold,scope.back().data(),CImg<T>::pixel_type(),cimg::t_normal);
    if (!is_debug && !is_quit && scope.size()==1 && is_default_type) {
      print(images,"End G'MIC parser.\n");
      is_quit = true;
    }
  } catch (CImgException &e) {
    CImg<char> error_message(e.what(),std::strlen(e.what())+1);
    for (char *cimg = std::strstr(error_message,"CImg"); cimg; cimg = std::strstr(cimg,"CImg")) {
      cimg[0] = 'g'; cimg[1] = 'm'; cimg[2] = 'i'; cimg[3] = 'c';
    }
    error(images,error_message);
  }
  return *this;
}

// Small hack to separate the compilation of G'MIC for different pixel types.
// (only intended to save computer memory when compiling!)
//--------------------------------------------------------------------------
#if !defined(gmic_float_only) && (defined(gmic_bool) || !defined(gmic_split_compilation))
gmic& gmic::parse_bool(const CImgList<char>& commands_line, unsigned int& position,
                       CImgList<bool>& images, CImgList<char>& images_names,
                        const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<bool>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<bool>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_bool) || !defined(gmic_split_compilation))
#if !defined(gmic_float_only) && (defined(gmic_uchar) || !defined(gmic_split_compilation))
gmic& gmic::parse_uchar(const CImgList<char>& commands_line, unsigned int& position,
                        CImgList<unsigned char>& images, CImgList<char>& images_names,
                        const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<unsigned char>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<unsigned char>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_uchar) || !defined(gmic_split_compilation))
#if !defined(gmic_float_only) && (defined(gmic_char) || !defined(gmic_split_compilation))
gmic& gmic::parse_char(const CImgList<char>& commands_line, unsigned int& position,
                       CImgList<char>& images, CImgList<char>& images_names,
                       const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<char>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<char>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_char) || !defined(gmic_split_compilation))
#if !defined(gmic_float_only) && (defined(gmic_ushort) || !defined(gmic_split_compilation))
gmic& gmic::parse_ushort(const CImgList<char>& commands_line, unsigned int& position,
                         CImgList<unsigned short>& images, CImgList<char>& images_names,
                         const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<unsigned short>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<unsigned short>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_ushort) || !defined(gmic_split_compilation))
#if !defined(gmic_float_only) && (defined(gmic_short) || !defined(gmic_split_compilation))
gmic& gmic::parse_short(const CImgList<char>& commands_line, unsigned int& position,
                        CImgList<short>& images, CImgList<char>& images_names,
                        const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<short>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<short>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_short) || !defined(gmic_split_compilation))
#if !defined(gmic_float_only) && (defined(gmic_uint) || !defined(gmic_split_compilation))
gmic& gmic::parse_uint(const CImgList<char>& commands_line, unsigned int& position,
                       CImgList<unsigned int>& images, CImgList<char>& images_names,
                       const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<unsigned int>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<unsigned int>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_uint) || !defined(gmic_split_compilation))
#if !defined(gmic_float_only) && (defined(gmic_int) || !defined(gmic_split_compilation))
gmic& gmic::parse_int(const CImgList<char>& commands_line, unsigned int& position,
                      CImgList<int>& images, CImgList<char>& images_names,
                      const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<int>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<int>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_int) || !defined(gmic_split_compilation))
#if defined(gmic_float) || !defined(gmic_split_compilation)
gmic& gmic::parse_float(const CImgList<char>& commands_line, unsigned int& position,
                        CImgList<float>& images, CImgList<char>& images_names,
                        const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<float>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<float>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if defined(gmic_float) || !defined(gmic_split_compilation)
#if !defined(gmic_float_only) && (defined(gmic_double) || !defined(gmic_split_compilation))
gmic& gmic::parse_double(const CImgList<char>& commands_line, unsigned int& position,
                         CImgList<double>& images, CImgList<char>& images_names,
                         const unsigned int (&variables_sizes)[256]) {
  return parse(commands_line,position,images,images_names,variables_sizes);
}
template gmic::gmic(const int, const char *const *const, CImgList<double>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
template gmic::gmic(const char *const, CImgList<double>&, CImgList<char>&,
                    const char *const custom_commands, const bool include_default_commands,
                    float *const p_progress, int *const p_cancel);
#endif // #if !defined(gmic_float_only) && (defined(gmic_double) || !defined(gmic_split_compilation))

#ifdef gmic_main

//-----------------------
// Start main procedure.
//-----------------------
int main(int argc, char **argv) {

  cimg::output(stdout);
  if (argc==1) {
    std::fprintf(cimg::output(),
                 "[gmic] No commands, options or data provided (type '%s -h' to get help).\n",
                 cimg::basename(argv[0]));
    std::fflush(cimg::output());
    std::exit(0);
  }

  // Check if help has been requested.
  char command_line[256] = { 0 };
  const char
    *const is_help1 = cimg_option("-h",(char*)0,0),
    *const is_help2 = cimg_option("--h",(char*)0,0),
    *const is_help3 = cimg_option("-help",(char*)0,0),
    *const is_help4 = cimg_option("--help",(char*)0,0);
  if (is_help1 || is_help2 || is_help3 || is_help4) {

    // Load all specified commands definitions data.
    CImgList<> images;
    CImgList<char> images_names;
    CImg<unsigned char>(data_gmic_def,1,size_data_gmic_def,1,1).move_to(images);
    const unsigned int omode = cimg::exception_mode();
    cimg::exception_mode() = 0;
    for (int i = 1; i<argc; ++i) {
      std::FILE *file = 0;
      char filename_tmp[1024] = { 0 };
      if ((!std::strcmp("-m",argv[i]) || !std::strcmp("-command",argv[i])) && i<argc-1) {
        const char *const filename = argv[++i];
        if (!cimg::strncasecmp(filename,"http://",7) || !cimg::strncasecmp(filename,"https://",8))
          try {
            file = std::fopen(cimg::load_network_external(filename,filename_tmp),"r");
          } catch (CImgException&) { file = 0; }
        else file = std::fopen(filename,"r");
      } else if (!cimg::strcasecmp("gmic",cimg::split_filename(argv[i]))) {
        const char *const filename = argv[i];
        if (!cimg::strncasecmp(filename,"http://",7) || !cimg::strncasecmp(filename,"https://",8))
          try {
            file = std::fopen(cimg::load_network_external(filename,filename_tmp),"r");
          } catch (CImgException&) { file = 0; }
        else file = std::fopen(filename,"r");
      }
      if (file) {
        CImg<unsigned char>::vector('\n').move_to(images);
        CImg<unsigned char>::get_load_raw(file).move_to(images);
        cimg::fclose(file);
        if (*filename_tmp) std::remove(filename_tmp);
      }
    }
    cimg::exception_mode() = omode;

    const char
      *const is_help = is_help1?"-h":is_help2?"--h":is_help3?"-help":"--help",
      *const command = is_help1?is_help1:is_help2?is_help2:is_help3?is_help3:is_help4;
    if (!std::strcmp(is_help,command)) gmic("-v - -help",images,images_names); // Global help.
    else { // Help for a specified command.
      cimg_snprintf(command_line,sizeof(command_line),"-v - -help \"%s\",1",command);
      gmic(command_line,images,images_names);
    }
    std::exit(0);
  }

  // Launch G'MIC instance.
  const char *const is_debug = cimg_option("-debug",(char*)0,0);
  cimg::output(is_debug?stdout:stderr);
  CImgList<float> images;
  CImgList<char> images_names;
  try { gmic(argc,argv,images,images_names); }
  catch (gmic_exception &e) {
    std::fprintf(cimg::output(),"\n[gmic] %s%s%s%s",
                 cimg::t_red,cimg::t_bold,e.what(),cimg::t_normal);
    if (*e.command()) {
      std::fprintf(cimg::output(),"\n[gmic] Command '%s' has the following description: \n",
                   e.command());
      images.assign(); images_names.assign();
      CImg<unsigned char>(data_gmic_def,1,size_data_gmic_def,1,1).move_to(images);
      cimg_snprintf(command_line,sizeof(command_line),"-v - -help \"%s\",0",e.command());
      gmic(command_line,images,images_names);
    } else { std::fprintf(cimg::output(),"\n\n"); std::fflush(cimg::output()); }
    return -1;
  }
  return 0;
}
#endif // #ifdef gmic_main

#endif // #ifdef cimg_plugin
