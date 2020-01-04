#include "Image.h"
#include "StickerSheet.h"

// A print function for debug
void StickerSheet::_print() {
    std::cout << "max = " << max_ << ", ct = " << ct_ << std::endl;
    for (unsigned i = 0; i < ct_; i++) {
        std::cout << stickers_[i];
        std::cout << " (" << x_[i] << ", " << y_[i] << ")" << std::endl; 
    }
    std::cout << "###############" << std::endl;
}

void StickerSheet::_clear() {
    if (baseImage_ != NULL) {
        delete baseImage_;
        baseImage_ = NULL;
    }
    if (x_ != NULL) {
        delete x_;
        x_ = NULL;
    }
    if (y_ != NULL) {
        delete y_;
        y_ = NULL;
    }
    for (unsigned i = 0; i < ct_; i++) {
        delete stickers_[i];
        stickers_[i] = NULL;
    }
    if (stickers_ != NULL) {
        delete[] stickers_;
        stickers_ = NULL;
    }
    ct_ = 0;
    max_ = 0;
}

void StickerSheet::_copy(const StickerSheet & other) {
    //_clear();
    this->baseImage_ = new Image(*other.baseImage_);
    this->max_ = other.max_;
    this->ct_ = other.ct_;
    this->stickers_ = new Image *[max_];    // * memory lost
    this->x_ = new unsigned[max_];
    this->y_ = new unsigned[max_];
    for (unsigned i = 0; i < ct_; i++) {
        this->stickers_[i] = new Image();
        *this->stickers_[i] = *other.stickers_[i];
        this->x_[i] = other.x_[i];
        this->y_[i] = other.y_[i];
    }
}

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    this->baseImage_ = new Image();
    *this->baseImage_ = picture;
    this->max_ = max;
    this->stickers_ = new Image *[max];     // * memory
    this->x_ = new unsigned[max];
    this->y_ = new unsigned[max];
    this->ct_ = 0;
}

StickerSheet::~StickerSheet() {
    _clear();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    _copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    if (this != &other) {
        _clear();
        _copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    StickerSheet * newSheet = new StickerSheet(*this->baseImage_, max);

    if (this->ct_ >= max) {
        newSheet->ct_ = max;
    } else {
        newSheet->ct_ = this->ct_;
    }

    for (unsigned i= 0; i < newSheet->ct_; i++) {
        newSheet->stickers_[i] = new Image(*this->stickers_[i]);
        newSheet->x_[i] = this->x_[i];
        newSheet->y_[i] = this->y_[i];
    }
    *this = *newSheet;
    delete newSheet;


    //std::cout << "changeMax" << std::endl;
    //_print();


}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    if (max_ <= ct_) {
        
        _print();

        return -1;
    }

    stickers_[ct_] = new Image(sticker);
    x_[ct_] = x;
    y_[ct_] = y;
    ct_++;


    //std::cout << "add" << std::endl;
    //_print();
    
    return ct_ - 1;
    
    /*
    Image * addSticker = new Image(sticker);
    for (unsigned i = 0; i < ct_ - 1; i++) {
        unsigned index = ct_ - i - 1;
        stickers_[index] = stickers_[index - 1];
        x_[index] = x_[index - 1];
        y_[index] = y_[index - 1];
    }
    stickers_[0] = addSticker;
    x_[0] = x;
    y_[0] = y;
    */
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= ct_) {
        _print();
        return;
    }

    delete stickers_[index];
    stickers_[index] = NULL;
    for (unsigned i = index; i < ct_; i++) {
        if (i == ct_ - 1) {
            stickers_[i] = NULL;
            x_[i] = -1;
            y_[i] = -1;
            break;
        }
        stickers_[i] = stickers_[i + 1];
        x_[i] = x_[i + 1];
        y_[i] = y_[i + 1];
    }
    ct_--;

    //std::cout << "remove" << std::endl;
    //_print();
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= ct_) {
        return false;
    }
    x_[index] = x;
    y_[index] = y;
    return true;
}

Image * StickerSheet::getSticker(unsigned index) {
    if (index >= ct_) {
        return NULL;
    } else {
        return this->stickers_[index];
    }
}

Image StickerSheet::render() const {

    //Image * scene = new Image(*this->baseImage_);  // Memory leak

    Image scene = *this->baseImage_;
    for (unsigned l = 0; l < ct_; l++) {
        Image * currSticker = stickers_[l];

        // Check whether we need to resize the scene or not.
        unsigned required_width = x_[l] + currSticker->width();
        unsigned required_height = y_[l] + currSticker->height();

        if (required_width > scene.width() || required_height > scene.height()) {
            if (required_width < scene.width()) {
                required_width = scene.width();
            }
            if (required_height < scene.height()) {
                required_height = scene.height();
            }
                    
            scene.resize(required_width, required_height);
        }

        // Draw the current sticker.
        for (unsigned i = 0; i < currSticker->width(); i++) {
            for (unsigned j = 0; j < currSticker->height(); j++) {

                HSLAPixel & pSticker = currSticker->getPixel(i, j);
                HSLAPixel & pScene = scene.getPixel(i + x_[l], j + y_[l]);
                if (pSticker.a == 0) {
                    continue;
                } else {
                    pScene = pSticker;
                }
            }
        }
    }
    return scene;
}