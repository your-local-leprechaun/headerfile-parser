#ifndef HEADERFILE_H
#define HEADERFILE_H

class HeaderFile {
    private:
        int x;
        void helperFunction();
    public:
        HeaderFile();
        void publicFunction();
        /**
         * Get the x Object
         * @return x 
         */
        int getX();
};

#endif