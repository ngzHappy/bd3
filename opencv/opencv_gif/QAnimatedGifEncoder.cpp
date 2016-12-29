/*
 * 抖动算法
 * http://blog.csdn.net/xiaojidan2011/article/details/7972710
*/

#include "QAnimatedGifEncoder.hpp"

#include <cmath>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>

#include <QtCore/QVector>
#include <QtGui/QPainter>

#include <Qt/boost/geometry/index/rtree.hpp>

#ifndef null
#define null 0
#endif

#ifndef one
#define one (Integer(1))
#endif

namespace {

inline void put_char(QIODevice * o,char c) {
    o->putChar(c);
}

}/*namespace*/

namespace mgui {

namespace {

constexpr const double uchar2doule[]{
    0/256.0,	1/256.0,	2/256.0,	3/256.0,	4/256.0,	5/256.0,	6/256.0,	7/256.0,	8/256.0,	9/256.0,	10/256.0,	11/256.0,	12/256.0,	13/256.0,	14/256.0,	15/256.0,
    16/256.0,	17/256.0,	18/256.0,	19/256.0,	20/256.0,	21/256.0,	22/256.0,	23/256.0,	24/256.0,	25/256.0,	26/256.0,	27/256.0,	28/256.0,	29/256.0,	30/256.0,	31/256.0,
    32/256.0,	33/256.0,	34/256.0,	35/256.0,	36/256.0,	37/256.0,	38/256.0,	39/256.0,	40/256.0,	41/256.0,	42/256.0,	43/256.0,	44/256.0,	45/256.0,	46/256.0,	47/256.0,
    48/256.0,	49/256.0,	50/256.0,	51/256.0,	52/256.0,	53/256.0,	54/256.0,	55/256.0,	56/256.0,	57/256.0,	58/256.0,	59/256.0,	60/256.0,	61/256.0,	62/256.0,	63/256.0,
    64/256.0,	65/256.0,	66/256.0,	67/256.0,	68/256.0,	69/256.0,	70/256.0,	71/256.0,	72/256.0,	73/256.0,	74/256.0,	75/256.0,	76/256.0,	77/256.0,	78/256.0,	79/256.0,
    80/256.0,	81/256.0,	82/256.0,	83/256.0,	84/256.0,	85/256.0,	86/256.0,	87/256.0,	88/256.0,	89/256.0,	90/256.0,	91/256.0,	92/256.0,	93/256.0,	94/256.0,	95/256.0,
    96/256.0,	97/256.0,	98/256.0,	99/256.0,	100/256.0,	101/256.0,	102/256.0,	103/256.0,	104/256.0,	105/256.0,	106/256.0,	107/256.0,	108/256.0,	109/256.0,	110/256.0,	111/256.0,
    112/256.0,	113/256.0,	114/256.0,	115/256.0,	116/256.0,	117/256.0,	118/256.0,	119/256.0,	120/256.0,	121/256.0,	122/256.0,	123/256.0,	124/256.0,	125/256.0,	126/256.0,	127/256.0,
    128/256.0,	129/256.0,	130/256.0,	131/256.0,	132/256.0,	133/256.0,	134/256.0,	135/256.0,	136/256.0,	137/256.0,	138/256.0,	139/256.0,	140/256.0,	141/256.0,	142/256.0,	143/256.0,
    144/256.0,	145/256.0,	146/256.0,	147/256.0,	148/256.0,	149/256.0,	150/256.0,	151/256.0,	152/256.0,	153/256.0,	154/256.0,	155/256.0,	156/256.0,	157/256.0,	158/256.0,	159/256.0,
    160/256.0,	161/256.0,	162/256.0,	163/256.0,	164/256.0,	165/256.0,	166/256.0,	167/256.0,	168/256.0,	169/256.0,	170/256.0,	171/256.0,	172/256.0,	173/256.0,	174/256.0,	175/256.0,
    176/256.0,	177/256.0,	178/256.0,	179/256.0,	180/256.0,	181/256.0,	182/256.0,	183/256.0,	184/256.0,	185/256.0,	186/256.0,	187/256.0,	188/256.0,	189/256.0,	190/256.0,	191/256.0,
    192/256.0,	193/256.0,	194/256.0,	195/256.0,	196/256.0,	197/256.0,	198/256.0,	199/256.0,	200/256.0,	201/256.0,	202/256.0,	203/256.0,	204/256.0,	205/256.0,	206/256.0,	207/256.0,
    208/256.0,	209/256.0,	210/256.0,	211/256.0,	212/256.0,	213/256.0,	214/256.0,	215/256.0,	216/256.0,	217/256.0,	218/256.0,	219/256.0,	220/256.0,	221/256.0,	222/256.0,	223/256.0,
    224/256.0,	225/256.0,	226/256.0,	227/256.0,	228/256.0,	229/256.0,	230/256.0,	231/256.0,	232/256.0,	233/256.0,	234/256.0,	235/256.0,	236/256.0,	237/256.0,	238/256.0,	239/256.0,
    240/256.0,	241/256.0,	242/256.0,	243/256.0,	244/256.0,	245/256.0,	246/256.0,	247/256.0,	248/256.0,	249/256.0,	250/256.0,	251/256.0,	252/256.0,	253/256.0,	254/256.0,	255/256.0,
};

template<typename T1,typename T>
static inline void writeSome(const T1 & some,T * out) {
    out->write((Byte *)(&some),sizeof(T1));
}

template<typename T>
static inline void writeSome(Integer some,T * out) {
    out->write((Byte *)(&some),sizeof(Integer));
}

template<typename T>
static inline void writeSome(Byte some,T * out) {
    out->write(&some,sizeof(Byte));
}

}/*namespace*/

}/*mgui*/

namespace mgui {

namespace {
//隐式数据共享
typedef  QVector<Byte>  PixType;

class QuantizationAlgorithm {
public:
    QuantizationAlgorithm() {}
    virtual void construct(const PixType & /*thepic*/,Integer /*len*/,Integer /*sample*/)=0;
    virtual ~QuantizationAlgorithm() {}
    virtual QVector<Byte> process()=0;
    virtual Integer map(Integer b,Integer g,Integer r)=0;
};

class Quantization :public QuantizationAlgorithm {

    static unsigned char int2unsignedchar(int i) {
        return (unsigned char)((i&0x00ff));
    }

public:

    struct DataItem {
        unsigned char a,b,c;
        DataItem():a(0),b(0),c(0) {}
        DataItem(
                unsigned char _0,
                unsigned char _1,
                unsigned char _2):a(_0),b(_1),c(_2) {
        }
        template<typename T0,typename T1,typename T2>
        DataItem(T0 _0,T1 _1,T2 _2):
            a(int2unsignedchar(_0)),
            b(int2unsignedchar(_1)),
            c(int2unsignedchar(_2)) {
        }
        friend bool operator<(const DataItem & l,const DataItem & r) {
            if (l.a<r.a) { return true; }
            if (l.a>r.a) { return false; }
            if (l.b<r.b) { return true; }
            if (l.b>r.b) { return false; }
            return l.c<r.c;
        }
    };

    PixType pix;
    QVector<Byte> quantization;
    typedef boost::geometry::model::point<
    std::int32_t,3,
    boost::geometry::cs::cartesian> point_t/*笛卡尔坐标系点*/;
    typedef std::pair<point_t,std::int32_t> value_t;
    typedef boost::geometry::index::rtree<value_t,boost::geometry::index::quadratic<16>> rtree_t;
    std::shared_ptr<rtree_t> rtree/*使用rtree加快搜索速度*/;

    void construct(
            const PixType & hepic,
            Integer /*len*/,
            Integer /*sample*/) override {
        pix=hepic;
    }

    QVector<Byte> process() {
        QVector<Byte> & ans=quantization;
        ans.clear();
        rtree=std::make_shared<rtree_t>();

        evalQuantization();

        return quantization;
    }

    Integer map(Integer _1_,Integer _2_,Integer _3_) {
        if (rtree) {
            point_t point(_1_,_2_,_3_);
            std::vector<value_t> ans;
            rtree->query(
                        boost::geometry::index::nearest(point,1),
                        std::back_inserter(ans));
            if (ans.empty()==false) {
                return ans[0].second;
            }
        }
        return 0;
    }

private:
    void evalQuantization() {

        std::map<DataItem,std::int32_t>hist;

        {/*得到统计值*/
            auto begin_=(const DataItem *)(pix.cbegin());
            auto end_=(const DataItem*)(pix.cend());
            for (auto pos=begin_; pos!=end_; ++pos) {
                auto hpos=hist.find(*pos);
                if (hpos!=hist.end()) {
                    ++(hpos->second);
                }
                else {
                    hist.insert({ *pos,1 });
                }
            }

        }

        /*颜色数小于等于256*/
        if (hist.size()<=256) {
            std::int32_t index_=0;
            for (auto & i:hist) {
                rtree->insert(std::make_pair(
                                  point_t(i.first.a,i.first.b,i.first.c),index_++
                                  ));
                quantization.push_back(Byte(i.first.a&0x00ff));
                quantization.push_back(Byte(i.first.b&0x00ff));
                quantization.push_back(Byte(i.first.c&0x00ff));
            }
            return;
        }

        /*降低颜色数目*/
        struct Data {
            double a,b,c;
            std::int32_t count;
        };

        struct Pack {
            std::list<Data>data;
            double mean_x,mean_y,mean_z;
            double std_x,std_y,std_z;

            void update() {
                double x=0,y=0,z=0;
                double x_w=0;

                for (const auto & i:(data)) {
                    x_w+=i.count;
                    x+=i.a*i.count;
                    y+=i.b*i.count;
                    z+=i.c*i.count;
                }

                mean_x=x/x_w;
                mean_y=y/x_w;
                mean_z=z/x_w;

                std_x=0; std_y=0; std_z=0;
                for (const auto & i:(data)) {

                    z=std::abs((i.c-mean_z));
                    y=std::abs((i.b-mean_y));
                    x=std::abs((i.a-mean_x));

                    if (x<0.5) { x/=2; }
                    if (y<0.5) { y/=2; }
                    if (z<0.5) { z/=2; }

                    std_x+=x*i.count;
                    std_y+=y*i.count;
                    std_z+=z*i.count;
                }

            }

            std::pair<
                    std::shared_ptr<Pack>,
                    std::shared_ptr<Pack>
                    >next() {
                if ((std_x>=std_y)&&(std_x>=std_z)) {
                    return split_x();
                }
                if ((std_y>=std_x)&&(std_y>=std_z)) {
                    return split_y();
                }
                return split_z();
            }

            std::pair<
                    std::shared_ptr<Pack>,
                    std::shared_ptr<Pack>
                    >split_x() {
                std::shared_ptr<Pack> l=std::make_shared<Pack>();
                std::shared_ptr<Pack> r=std::make_shared<Pack>();

                for (const Data & i:data) {
                    if (i.a>mean_x) { l->data.push_back(i); }
                    else { r->data.push_back(i); }
                }

                l->update(); r->update();
                return{ std::move(l),std::move(r) };
            }
            std::pair<
                    std::shared_ptr<Pack>,
                    std::shared_ptr<Pack>
                    >split_y() {
                std::shared_ptr<Pack> l=std::make_shared<Pack>();
                std::shared_ptr<Pack> r=std::make_shared<Pack>();

                for (const Data & i:data) {
                    if (i.b>mean_y) { l->data.push_back(i); }
                    else { r->data.push_back(i); }
                }

                l->update(); r->update();
                return{ std::move(l),std::move(r) };
            }
            std::pair<
                    std::shared_ptr<Pack>,
                    std::shared_ptr<Pack>
                    >split_z() {
                std::shared_ptr<Pack> l=std::make_shared<Pack>();
                std::shared_ptr<Pack> r=std::make_shared<Pack>();

                for (const Data & i:data) {
                    if (i.c>mean_z) { l->data.push_back(i); }
                    else { r->data.push_back(i); }
                }

                l->update(); r->update();
                return{ std::move(l),std::move(r) };
            }
        };

        auto comp_pack_function=[](
                std::shared_ptr<Pack> &l,
                std::shared_ptr<Pack> &r
                ) {
            auto std_l=(l->std_z+(l->std_x+l->std_y));
            auto std_r=(r->std_x+(r->std_y+r->std_z));
            return std_l>std_r;
        };

        std::vector<std::shared_ptr<Pack>> packs;
        packs.reserve(256);
        {
            auto pack_root=std::make_shared<Pack>();
            for (const auto & i:hist) {
                pack_root->data.push_back({
                                              uchar2doule[i.first.a],
                                              uchar2doule[i.first.b],
                                              uchar2doule[i.first.c],
                                              i.second
                                          }
                                          );
            }
            pack_root->update();
            packs.push_back(std::move(pack_root));
        }

        hist.clear();
        while (packs.size()<256) {
            std::sort(packs.begin(),packs.end(),comp_pack_function);
            auto next_=packs.begin()->get()->next();
            packs[0]=next_.first;
            packs.push_back(next_.second);
        }

        std::int32_t index=0;
        for (auto & p:packs) {

            p->mean_x*=256.66;
            p->mean_y*=256.66;
            p->mean_z*=256.66;

            std::int32_t a,b,c;
            a=std::int32_t(std::round(p->mean_x));
            b=std::int32_t(std::round(p->mean_y));
            c=std::int32_t(std::round(p->mean_z));

            if (a>255) { a=255; }
            if (b>255) { b=255; }
            if (c>255) { c=255; }

            rtree->insert(std::make_pair(
                              point_t(a,b,c),index++
                              ));

            quantization.push_back(Byte(a&0x00ff));
            quantization.push_back(Byte(b&0x00ff));
            quantization.push_back(Byte(c&0x00ff));

            p.reset();
        }

    }
};

}/*namespace*/
}/*mgui*/

namespace mgui {
namespace {

class LZWEncoder {
public:
    using const_uchar=const unsigned char;
    using type_uchar=unsigned char;
private:
    inline static void put_char(QIODevice * o,const_uchar & c) {
        o->putChar(static_cast<const char &>(c));
    }
    inline static void write_chars(QIODevice * o,const_uchar * d,Integer s) {
        o->write(reinterpret_cast<const char*>(d),s);
    }
public:

#ifndef EOF
    static constexpr Integer EOF=-1; /*= -1*/
#endif

    enum :Integer {
        BITS=12,
        HSIZE=5003,
        ACCUM_SIZE=256,
        MASKS_SIZE=17,
        MAX_UCHAR=255,
    };

    std::array<Integer,HSIZE> htab;
    std::array<Integer,HSIZE> codetab;
    std::array<type_uchar,ACCUM_SIZE> accum/*缓存区*/;

    Integer imgW=0;
    Integer imgH=0;
    Integer initCodeSize=0;
    Integer remaining=0;
    Integer curPixel=0;
    Integer n_bits=0; /*number of bits/code*/
    Integer maxbits=BITS; /*user settable max # bits/code*/
    Integer maxcode=0; /*maximum code, given n_bits*/
    Integer maxmaxcode=(1<<BITS); /*should NEVER generate this code*/
    Integer hsize=HSIZE; /*for dynamic table sizing*/
    Integer free_ent=0; /*first unused entry*/
    Boolean clear_flg=false;
    Integer g_init_bits=0;
    Integer ClearCode=0;
    Integer EOFCode=0;
    Integer cur_accum=0;
    Integer cur_bits=0;

    template<typename T>
    static inline Integer masks(T arg) {
        assert(arg<MASKS_SIZE);
        assert(arg>=0);
        static constexpr Integer masks[MASKS_SIZE]{
            0x00000000,/*0*/
            0x00000001,/*1*/
            0x00000003,/*2*/
            0x00000007,/*3*/
            0x0000000F,/*4*/
            0x0000001F,/*5*/
            0x0000003F,/*6*/
            0x0000007F,/*7*/
            0x000000FF,/*8*/
            0x000001FF,/*9*/
            0x000003FF,/*10*/
            0x000007FF,/*11*/
            0x00000FFF,/*12*/
            0x00001FFF,/*13*/
            0x00003FFF,/*14*/
            0x00007FFF,/*15*/
            0x0000FFFF,/*16*/
        };
        static_assert(sizeof(masks)/sizeof(Integer)==MASKS_SIZE,"");
        return masks[arg];
    }

    Integer a_count=0;

    const_uchar * pixAryBegin=nullptr;
    const_uchar * pixAryEnd=nullptr;
private:
    LZWEncoder() {}
public:
    //----------------------------------------------------------------------------
    LZWEncoder(
            Integer width/*image width*/,
            Integer height/*image height*/,
            const_uchar * argPixAryBegin/*image data char8_t*/,
            const_uchar * argPixAryEnd/*image data char8_t*/,
            Integer color_depth):LZWEncoder() {
        imgW=width;
        imgH=height;
        pixAryBegin=argPixAryBegin;
        pixAryEnd=argPixAryEnd;
        initCodeSize=(std::max)(2,color_depth);
    }

    void char_out(type_uchar c,OutputStream * outs) {
        accum[a_count++]=c;
        if (a_count>=254) {
            flush_char(outs);
        }
    }

    /*Clear out the hash table*/
    /*table clear for block compress*/
    void cl_block(OutputStream * outs) {
        cl_hash(hsize);
        free_ent=ClearCode+2;
        clear_flg=true;
        output(ClearCode,outs);
    }

    /*reset code table*/
    void cl_hash(const Integer hsize) {
        for (Integer i=0; i<hsize; ++i){
            htab[i]=-1;
        }
    }

    void compress(Integer init_bits,OutputStream *outs) {
        Integer fcode=0;
        Integer i=0;
        Integer c=0;
        Integer ent=0;
        Integer disp=0;
        Integer hsize_reg=0;
        Integer hshift=0;
        /*Set up the globals:  g_init_bits - initial number of bits*/
        g_init_bits=init_bits;
        /*Set up the necessary values*/
        clear_flg=false;
        n_bits=g_init_bits;
        maxcode=MAXCODE(n_bits);
        ClearCode=1<<(init_bits-1);
        EOFCode=ClearCode+1;
        free_ent=ClearCode+2;
        a_count=0; /*clear packet*/
        ent=nextPixel();
        hshift=0;
        for (fcode=hsize; fcode<65536; fcode*=2) {
            ++hshift;
        }
        hshift=8-hshift; /*set hash code range bound*/
        hsize_reg=hsize;
        cl_hash(hsize_reg); /*clear hash table*/
        output(ClearCode,outs);

outer_loop:
        while ((c=nextPixel())!=EOF) {
            fcode=(c<<maxbits)+ent;
            i=(c<<hshift)^ent; /*xor hashing*/
            if (htab[i]==fcode) {
                ent=codetab[i];
                continue;
            }
            else if (htab[i]>=0) /*non-empty slot*/ {
                disp=hsize_reg-i; /*secondary hash (after G. Knott)*/
                if (i==0) {
                    disp=1;
                }
                do {
                    if ((i-=disp)<0)
                        i+=hsize_reg;
                    if (htab[i]==fcode) {
                        ent=codetab[i];
                        goto outer_loop;
                    }
                } while (htab[i]>=0);
            }
            output(ent,outs);
            ent=c;
            if (free_ent<maxmaxcode) {
                codetab[i]=free_ent++; // code -> hashtable
                htab[i]=fcode;
            }
            else {
                cl_block(outs);
            }
        }

        /* Put out the final code.*/
        output(ent,outs);
        output(EOFCode,outs);

    }

    /*----------------------------------------------------------------------------*/
    void encode(OutputStream * os) {
        assert(initCodeSize<=MAX_UCHAR);
        assert(initCodeSize>=0);
        this->put_char(os,initCodeSize); /*write "initial code size" byte*/
        remaining=imgW * imgH; /*reset navigation variables*/
        curPixel=0;
        compress(initCodeSize+1,os); /*compress and write the pixel data*/
        this->put_char(os,type_uchar(0));
    }

    /*Flush the packet to disk, and reset the accumulator*/
    void flush_char(OutputStream * outs) {
        if (a_count>0) {
            assert(a_count<=MAX_UCHAR);
            assert(a_count>=0);
            this->put_char(outs,a_count);
            this->write_chars(outs,accum.data(),a_count);
            a_count=0;
        }
    }

    static constexpr inline Integer MAXCODE(Integer n_bits) {
        return (1<<n_bits)-1;
    }

    //----------------------------------------------------------------------------
    // Return the next pixel from the image
    //----------------------------------------------------------------------------
    Integer nextPixel() {
        if (remaining==0) {
            return EOF;
        }
        --remaining;
        type_uchar pix=pixAryBegin[curPixel++];
        return pix;
    }

    void output(Integer code,OutputStream * outs) {
        cur_accum&=masks(cur_bits);

        if (cur_bits>0) {
            cur_accum|=(code<<cur_bits);
        }
        else {
            cur_accum=code;
        }

        cur_bits+=n_bits;

        while (cur_bits>=8) {
            assert(cur_accum<=MAX_UCHAR);
            assert(cur_accum>=0);
            char_out(cur_accum,outs);
            cur_accum>>=8;
            cur_bits-=8;
        }

        /*If the next entry is going to be too big for the code size,*/
        /*then increase it, if possible.*/
        if (free_ent>maxcode||clear_flg) {
            if (clear_flg) {
                maxcode=MAXCODE(n_bits=g_init_bits);
                clear_flg=false;
            }
            else {
                ++n_bits;
                if (n_bits==maxbits)
                    maxcode=maxmaxcode;
                else
                    maxcode=MAXCODE(n_bits);
            }
        }

        if (code==EOFCode) {
            /*At EOF, write the rest of the buffer.*/
            while (cur_bits>0) {
                assert(cur_accum>=0);
                assert(cur_accum<=MAX_UCHAR);
                char_out(cur_accum,outs);
                cur_accum>>=8;
                cur_bits-=8;
            }
            flush_char(outs);
        }

    }

};/*LZWEncoder*/

}/*namespace*/
}/*mgui*/

namespace mgui {
class QAnimatedGifEncoder::ThisData {
public:
    ThisData() {
        for (auto & ii:usedEntry) { ii=false; }
    }
    ~ThisData() {}

    Integer width=null; // image size
    Integer height=null;
    Color transparent=null; // transparent color if given
    Boolean isGivenTransparent=false;
    Integer transIndex=null; // transparent index in color table
    Integer repeat=-1; // no repeat
    Integer delay=0; // frame delay (hundredths)
    Boolean started=false; // ready to output frames
    OutputStream * out=0;
    BufferedImage image; // current frame
    PixType  pixels; // BGR byte array from frame
    QVector<Byte> indexedPixels; // converted frame indexed to palette
    Integer colorDepth=8; // number of bit planes
    QVector<Byte> colorTab; // RGB palette
    Boolean usedEntry[256]; // active palette entries
    Integer palSize=7; // color table size (bits-1)
    Integer dispose=-1; // disposal code (-1 = use default)
    Boolean closeStream=false; // close stream when finished
    Boolean firstFrame=true;
    Boolean sizeSet=false; // if false, get size from first frame
    Integer sample=10; // default sample interval for quantizer
};

QAnimatedGifEncoder::QAnimatedGifEncoder() {
    ThisData * var_thisData=new ThisData;
    thisData={
        var_thisData,
        [](ThisData * par_data) {delete par_data; }
    };
}


QAnimatedGifEncoder::~QAnimatedGifEncoder() {
    if (this->thisData->started)
        this->finish();
}

void QAnimatedGifEncoder::setDelay(const Integer ms) {
    ThisData * var_thisData=thisData.get();
    var_thisData->delay=std::round(ms/10.0f);
}

void QAnimatedGifEncoder::setDispose(const Integer code) {
    if (code>=0) {
        ThisData * var_thisData=thisData.get();
        var_thisData->dispose=code;
    }
}

void QAnimatedGifEncoder::setRepeat(const Integer iter) {
    if (iter>=0) {
        ThisData * var_thisData=thisData.get();
        var_thisData->repeat=iter;
    }
}

void QAnimatedGifEncoder::setTransparent(const Color c) {
    ThisData * var_thisData=thisData.get();
    var_thisData->isGivenTransparent=true;
    var_thisData->transparent=c;
}

void QAnimatedGifEncoder::setSize(const Integer w,const Integer h) {
    ThisData * var_thisData=thisData.get();
    if ((var_thisData->started)&&(!(var_thisData->firstFrame))) return;

    var_thisData->width=w;
    var_thisData->height=h;

    if (var_thisData->width<1) var_thisData->width=320;
    if (var_thisData->height<1) var_thisData->height=240;

    var_thisData->sizeSet=true;
}

namespace {

inline QImage change_image_format_and_size(
        const QImage & argImage,
        Integer argWidth,
        Integer argHeight
        ) {

    if (argImage.isNull()) {
        return QImage{ argWidth,argHeight,QImage::Format::Format_RGB888 };
    }

    QImage varAns=argImage;
    {
        QImage::Format varType=varAns.format();
        if (varType!=QImage::Format::Format_RGB888) {
            varAns=varAns.convertToFormat(QImage::Format::Format_RGB888);
        }
    }

    const auto varWidth=varAns.width();
    const auto varHeight=varAns.height();

    if ((varHeight!=argHeight)||(varWidth!=argWidth)) {
        varAns=varAns.scaled(argWidth,argHeight,
                             Qt::AspectRatioMode::IgnoreAspectRatio,
                             Qt::TransformationMode::SmoothTransformation);
    }

    return std::move(varAns);
}

}/*namespace*/

void QAnimatedGifEncoder::getImagePixels() {
    ThisData * var_thisData=thisData.get();

    var_thisData->image=change_image_format_and_size(
                var_thisData->image,
                var_thisData->width,
                var_thisData->height);

    {//set bits
        const auto var_w=var_thisData->image.width();
        const auto var_h=var_thisData->image.height();
        const QImage & varImage=var_thisData->image;
        auto & pixs=var_thisData->pixels;
        pixs.clear();
        pixs.reserve(var_w*var_h);


        auto varData=varImage.constBits();
        const auto varBytesPerLine=varImage.bytesPerLine();

        for (auto ii=0; ii<var_h; ++ii,varData+=varBytesPerLine) {
            auto varDataLine=varData;
            for (auto jj=0; jj<var_w; ++jj) {
                pixs.push_back(*reinterpret_cast<const Byte*>(varDataLine++));
                pixs.push_back(*reinterpret_cast<const Byte*>(varDataLine++));
                pixs.push_back(*reinterpret_cast<const Byte*>(varDataLine++));
            }
        }
    }

}


Boolean QAnimatedGifEncoder::addFrame(BufferedImage && im) {
    ThisData * var_thisData=thisData.get();
    if ((im.width()<=null)||!var_thisData->started) {
        return false;
    }
    Boolean ok=true;

    if (false==var_thisData->sizeSet) {
        // use first frame's size
        setSize(im.width(),im.height());
    }

    var_thisData->image=im;
    var_thisData->image=var_thisData->image.scaled(
                QSize(var_thisData->width,var_thisData->height),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation
                );

    getImagePixels(); // convert to correct format if necessary
    analyzePixels(); // build color table & map pixels

    if (var_thisData->firstFrame) {
        writeLSD(); // logical screen descriptior 逻辑屏幕标识符
        writePalette(); // global color table
        if (var_thisData->repeat>=0) {
            // use NS app extension to indicate reps
            writeNetscapeExt();
        }
    }

    writeGraphicCtrlExt(); // write graphic control extension
    writeImageDesc(); // image descriptor
    if (!(var_thisData->firstFrame)) {
        writePalette(); // local color table
    }
    writePixels(); // encode and write pixel data
    var_thisData->firstFrame=false;

    return ok;
}

void QAnimatedGifEncoder::writePalette() {
    ThisData * var_thisData=thisData.get();
    var_thisData->out->write(var_thisData->colorTab.data(),var_thisData->colorTab.size());
    Integer n=(3*256)-var_thisData->colorTab.size();
    for (Integer i=0; i<n; ++i) {
        writeSome(Byte(0),var_thisData->out);
    }
}

void QAnimatedGifEncoder::writePixels() {
    ThisData * var_thisData=thisData.get();
    LZWEncoder * encoder=
            new LZWEncoder(
                var_thisData->width,
                var_thisData->height,
                reinterpret_cast<LZWEncoder::const_uchar *>(var_thisData->indexedPixels.cbegin()),
                reinterpret_cast<LZWEncoder::const_uchar *>(var_thisData->indexedPixels.cend()),
                var_thisData->colorDepth
                );
    std::unique_ptr<LZWEncoder> _(encoder);
    encoder->encode(var_thisData->out);
}

void QAnimatedGifEncoder::writeGraphicCtrlExt() {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,(0x21)); // extension introducer
    put_char(var_thisData->out,(Byte(0xf9))); // GCE label
    put_char(var_thisData->out,(4)); // data block size
    Integer transp,disp;
    if (var_thisData->isGivenTransparent==false) {
        transp=0;
        disp=0; // dispose = no action
    }
    else {
        transp=1;
        disp=2; // force clear if using transparent color
    }
    if (var_thisData->dispose>=0) {
        disp=var_thisData->dispose&7; // user override
    }
    disp<<=2;
    // packed fields
    put_char(var_thisData->out,(Byte((disp|transp)&0x00ff))); // 8   transparency flag
    writeShort(var_thisData->delay); // delay x 1/100 sec
    put_char(var_thisData->out,(Byte(0x00ff&var_thisData->transIndex))); // transparent color index
    put_char(var_thisData->out,(0)); // block terminator
}

void QAnimatedGifEncoder::writeLSD() {
    ThisData * var_thisData=thisData.get();
    // logical screen size
    writeShort(var_thisData->width);
    writeShort(var_thisData->height);
    // packed fields
    writeSome(Byte(0x80|0x70|0x00|var_thisData->palSize),var_thisData->out);
    writeSome(Byte(0),var_thisData->out);
    writeSome(Byte(0),var_thisData->out);
}

void QAnimatedGifEncoder::writeImageDesc() {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,(0x2c));
    writeShort(0); // image position x,y = 0,0
    writeShort(0);
    writeShort(var_thisData->width); // image size
    writeShort(var_thisData->height);
    // packed fields
    if (var_thisData->firstFrame) {
        // no LCT  - GCT is used for first (or only) frame
        put_char(var_thisData->out,(0));
    }
    else {
        // specify normal LCT
        put_char(var_thisData->out,(0x80|var_thisData->palSize)); // 6-8 size of color table
    }
}

void QAnimatedGifEncoder::writeShort(Integer value) {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,(Byte(value&0x00ff)));
    put_char(var_thisData->out,(Byte((value>>8)&0x00ff)));
}

void QAnimatedGifEncoder::writeNetscapeExt() {
    ThisData * var_thisData=thisData.get();
    put_char(var_thisData->out,(0x21)); // extension introducer
    writeSome(Byte(0xff),var_thisData->out); // app extension label
    put_char(var_thisData->out,(11)); // block size
    writeString((const Byte *)("NETSCAPE2.0")); // app id + auth code
    put_char(var_thisData->out,(3)); // sub-block size
    put_char(var_thisData->out,(1)); // loop sub-block id
    writeShort(var_thisData->repeat); // loop count (extra iterations, 0=repeat forever)
    put_char(var_thisData->out,(0)); // block terminator
}

Boolean QAnimatedGifEncoder::addFrame(const BufferedImage & im) {
    BufferedImage var_image=im;
    return addFrame(std::move(var_image));
}

static inline const Byte * gifTrailer() {//1
    static const Byte data[]={ 0x3b, 0 };
    return data;
}

static inline const Byte * gifHeader() {//6
    static const Byte data[]={ 'G', 'I', 'F', '8', '9', 'a', 0 };
    return data;
}

Boolean QAnimatedGifEncoder::finish() {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->started==false) return false;
    Boolean ok=true;
    var_thisData->started=false;
    //
    if (var_thisData->out==0) { ok=false; }
    else
        try {
        put_char(var_thisData->out,(0x3b));
        if (var_thisData->closeStream) {
            var_thisData->out->close();
        }
    }
    catch (...) {
        ok=false;
    }

    // reset for subsequent use
    var_thisData->transIndex=0;
    var_thisData->out=null;
    var_thisData->image=QImage();
    var_thisData->pixels.clear();
    var_thisData->indexedPixels.clear();
    var_thisData->colorTab.clear();
    var_thisData->closeStream=false;
    var_thisData->firstFrame=true;
    var_thisData->isGivenTransparent=false;

    return ok;
}

void QAnimatedGifEncoder::setFrameRate(const Float fps) {
    if (fps!=0.0f) {
        ThisData * var_thisData=thisData.get();
        var_thisData->delay=std::round(100.0f/fps);
    }
}

void QAnimatedGifEncoder::setQuality(const Integer quality) {
    ThisData * var_thisData=thisData.get();
    if (quality<1) {
        var_thisData->sample=1;
        return;
    }
    var_thisData->sample=quality;
}

/* 'G', 'I', 'F', '8', '9', 'a' */
Boolean QAnimatedGifEncoder::start(OutputStream & os) {
    ThisData * var_thisData=thisData.get();
    Boolean ok=true;
    var_thisData->closeStream=false;
    var_thisData->out=&os;

    try {
        writeString(gifHeader()); // header
    }
    catch (...) {
        ok=false;
    }
    var_thisData->started=ok;
    return ok;
}

Integer QAnimatedGifEncoder::findClosest(Color c) {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->colorTab.size()==null) return -1;
    Integer r=qRed(c);
    Integer g=qGreen(c);
    Integer b=qBlue(c);
    Integer minpos=0;
    Integer dmin=256*256*256;
    Integer len=Integer(var_thisData->colorTab.size());
    for (Integer i=0; i<len;) {
        Integer dr=r-(var_thisData->colorTab[i++]&0xff);
        Integer dg=g-(var_thisData->colorTab[i++]&0xff);
        Integer db=b-(var_thisData->colorTab[i]&0xff);
        Integer d=dr * dr+dg * dg+db * db;
        Integer index=i/3;
        if (var_thisData->usedEntry[index]&&(d<dmin)) {
            dmin=d;
            minpos=index;
        }
        ++i;
    }
    return minpos;
}

//TODO:analyzePixels
void QAnimatedGifEncoder::analyzePixels() {
    ThisData * var_thisData=thisData.get();
    typedef Integer size_type;
    auto len=size_type(var_thisData->pixels.size());
    auto nPix=len/size_type(3);
    var_thisData->indexedPixels.resize(nPix);
    QuantizationAlgorithm * nq=new Quantization;//new NeuQuant;
    std::unique_ptr<QuantizationAlgorithm> uptr_nq(nq);
    nq->construct(var_thisData->pixels,len,var_thisData->sample);
    var_thisData->colorTab=nq->process();

    // map image pixels to new palette
    Integer k=0;
    for (Integer i=0; i<nPix; ++i) {
        /*java规定求值顺序从左至右 但是C/C++无此规定*/
        const Integer k0=k++;
        const Integer k1=k++;
        const Integer k2=k++;

        Integer index=
                nq->map(
                    Integer(var_thisData->pixels[k0])&0x00ff,
                    Integer(var_thisData->pixels[k1])&0x00ff,
                    Integer(var_thisData->pixels[k2])&0x00ff
                    );
        var_thisData->usedEntry[index]=true;
        var_thisData->indexedPixels[i]=(Byte)(index&0x000000ff);
    }
    var_thisData->pixels.clear();
    var_thisData->colorDepth=8;
    var_thisData->palSize=7;
    // get closest match to transparent color if specified
    if (var_thisData->isGivenTransparent) {//----
        var_thisData->transIndex=findClosest(var_thisData->transparent);
    }
}

void QAnimatedGifEncoder::writeString(const String & s) {
    ThisData * var_thisData=thisData.get();
    if (var_thisData->out&&s.size()) {
        auto string_=s.toUtf8();
        var_thisData->out->write(string_.data(),string_.size());
    }
}

}/*mgui*/

