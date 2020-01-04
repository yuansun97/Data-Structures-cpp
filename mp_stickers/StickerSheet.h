/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

class StickerSheet {
    private:
    Image *baseImage_;
    unsigned max_;
    Image ** stickers_;
    unsigned *x_;
    unsigned *y_;
    unsigned ct_;

    void _clear();
    void _copy(const StickerSheet & other);
    void _print();

    public:
    StickerSheet(const Image & picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet & other);

    const StickerSheet & operator=(const StickerSheet & other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image & sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);
    Image render() const;
};