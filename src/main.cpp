#include <sil/sil.hpp>
#include <iostream>
#include <string>

void keep_green_only(sil::Image& image) {
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
};

void swap_canal_red_and_blue(sil::Image& image) {
    float chair {0.f};
    for (glm::vec3& color : image.pixels())
    {
        chair = color.r;
        color.r = color.b;
        color.b = chair;
        //ou ceci :
        // std::swap(color.r, color.b);
    }
};

void black_and_white(sil::Image& image) {
    for (glm::vec3& color : image.pixels())
    {
        float gray_area = (color.b + color.r + color.g)/3.f;
        color.r = gray_area;
        color.g = gray_area;
        color.b = gray_area;
    }
};

void negative(sil::Image& image) {
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1.f-color.r;
        color.g = 1.f-color.g;
        color.b = 1.f-color.b;
    }
};

void gradient(sil::Image& image, int width) {
    float const pas = 1.f/width;
    float color_gradient {0.f};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = color_gradient;
            image.pixel(x, y).g = color_gradient;
            image.pixel(x, y).b = color_gradient;
        }
        color_gradient += pas;
    }
};

void mirrorside(sil::Image& image) {
    int const width = image.width()-1;
    for (int x{0}; x < image.width()/2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y).r, image.pixel(width-x,y).r);
            std::swap(image.pixel(x,y).b, image.pixel(width-x,y).b);
            std::swap(image.pixel(x,y).g, image.pixel(width-x,y).g);
        }
    }
};

void noise(sil::Image& image) {
    float alea_color {0.f};
    int const percentage_of_noise {20};
    for (glm::vec3& color : image.pixels())
    {
        //generation nombre aléatoire pour si on change le pixel
        int random_number_between_1_and_10_included {std::rand()%100 +1};
        if(random_number_between_1_and_10_included <= percentage_of_noise) {
            alea_color = (float)rand() / (float)RAND_MAX;
            color.r = alea_color;

            alea_color = (float)rand() / (float)RAND_MAX;
            color.g = alea_color;

            alea_color = (float)rand() / (float)RAND_MAX;
            color.b = alea_color;
        }
    }
};

void turning_90_degrees_right(sil::Image& image) {
    sil::Image image_turned{image.height()/*width*/, image.width()/*height*/};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y).r, image_turned.pixel(y,x).r);
            std::swap(image.pixel(x,y).b, image_turned.pixel(y,x).b);
            std::swap(image.pixel(x,y).g, image_turned.pixel(y,x).g);
        }
        image_turned.save("output/turning_90_degrees_right.png");
    }
};

void turning_90_degrees_left(sil::Image& image) {
    sil::Image image_turned{image.height()/*width*/, image.width()/*height*/};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x,y).r, image_turned.pixel(image.height()-y-1,image.width()-x-1).r);
            std::swap(image.pixel(x,y).b, image_turned.pixel(image.height()-y-1,image.width()-x-1).b);
            std::swap(image.pixel(x,y).g, image_turned.pixel(image.height()-y-1,image.width()-x-1).g);
        }
        image_turned.save("output/turning_90_degrees_left.png");
    }
};

void rgb_split(sil::Image& image) {
    //vert ne bouge pas
    //rouge va vers la droite
    //bleu va vers la gauche

    unsigned int const decalage_px {25};
    
    //bleu
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(x-decalage_px < 0) {
                image.pixel(x,y).b = 0.f;
            } else {
                std::swap(image.pixel(x,y).b, image.pixel(x-decalage_px,y).b);
            }
        }
    }

    //rouge
    for (int x{image.width()-1}; x >= 0; x--)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(x+decalage_px >= image.width()) {
                image.pixel(x,y).r = 0.f;
            } else {
                std::swap(image.pixel(x,y).r, image.pixel(x+decalage_px,y).r);
            }
        }
    }
};

void brightening(sil::Image& image) {
    float const add {0.5f};
    for (glm::vec3& color : image.pixels())
    {
        color.r = sqrt(color.r);
        color.g = sqrt(color.g);
        color.b = sqrt(color.b);
    }
};

void darkening(sil::Image& image) {
    float const substract {0.5f};
    for (glm::vec3& color : image.pixels())
    {
        color.r = pow(color.r, 2);
        color.g = pow(color.g, 2);
        color.b = pow(color.b, 2);
    }
};

void create_a_circle(sil::Image& image) {
    unsigned int const radius_circle {100};
    int const center_x {image.width()/2};
    int const center_y {image.height()/2};
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //si le point est dans le cercle
            if(static_cast<int>(sqrt((pow((x-center_x), 2)+pow((y-center_y), 2)))) < radius_circle) {
               image.pixel(x,y).r = 1.f;
               image.pixel(x,y).g = 1.f;
               image.pixel(x,y).b = 1.f;
            }
        }
    }
};

void create_border_circle(sil::Image& image) {
    unsigned int const radius_circle {100};
    unsigned int const thickness {10};
    int const center_x {image.width()/2};
    int const center_y {image.height()/2};
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int distance_from_the_center = static_cast<int>(sqrt((pow((x-center_x), 2)+pow((y-center_y), 2))));
            //si le point est dans le cercle
            if( distance_from_the_center < radius_circle && distance_from_the_center > radius_circle-thickness) {
               image.pixel(x,y).r = 1.f;
               image.pixel(x,y).g = 1.f;
               image.pixel(x,y).b = 1.f;
            }
        }
    }
};

void create_an_animation(sil::Image& image) {
    unsigned int const radius_circle {100};
    int center_x {0};
    int const center_y {image.height()/2};
    int const number_of_frames {5};
    int const pas {image.width()/number_of_frames};
    
    for (int i {}; i < number_of_frames; i++)
    {
        // creation du cercle
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                //si le point est dans le cercle
                if(static_cast<int>(sqrt((pow((x-center_x), 2)+pow((y-center_y), 2)))) < radius_circle) {
                image.pixel(x,y).r = 1.f;
                image.pixel(x,y).g = 1.f;
                image.pixel(x,y).b = 1.f;
                }
            }
        }
        //sauvegarde de la frame
        image.save("output/animation/"+ std::to_string(i) +".png");

        //reinitialisation de l'img
        for (glm::vec3& color : image.pixels())
        {
            color.r = 0.f;
            color.g = 0.f;
            color.b = 0.f;
        }

        //decalage du cercle
        center_x += pas;
    }
};

void rosace(sil::Image& image) {
    unsigned int const radius_circle {100};
    unsigned int const thickness {5};
    double const pas_angle {60*M_PI/180};
    int center_x {image.width()/2};
    int center_y {image.height()/2};
    
    //creation du 1er cercle avec bordure
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int distance_from_the_center = static_cast<int>(sqrt((pow((x-center_x), 2)+pow((y-center_y), 2))));
            //si le point est dans le cercle
            if( distance_from_the_center < radius_circle+thickness/2 && distance_from_the_center > radius_circle-thickness/2) {
               image.pixel(x,y).r = 1.f;
               image.pixel(x,y).g = 1.f;
               image.pixel(x,y).b = 1.f;
            }
        }
    }

    //creation des cercles sur le cercle n°1
    for (double angle {0}; angle < 2*M_PI; angle+=pas_angle)
    {
        //calcul du centre du nouveau cercle
        center_x = static_cast<int>(radius_circle*cos(angle)+image.width()/2 /*pour recentrer*/);
        center_y = static_cast<int>(radius_circle*sin(angle)+image.height()/2 /*pour recentrer*/);
        //creation du nouveau cercle en fonction du nouveau centre
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                int distance_from_the_center = static_cast<int>(sqrt((pow((x-center_x), 2)+pow((y-center_y), 2))));
                //si le point est dans le cercle
                if( (distance_from_the_center < radius_circle+thickness/2) && (distance_from_the_center > radius_circle-thickness/2)) {
                image.pixel(x,y).r = 1.f;
                image.pixel(x,y).g = 1.f;
                image.pixel(x,y).b = 1.f;
                }
            }
        }
    }  
};

void mosaique(sil::Image& image) {
    sil::Image image_mosaique{image.width()/*width*/, image.height()/*height*/};
    unsigned int const number_of_repetition {5};

    //repetition en x
    for (int i {}; i < number_of_repetition; i++)
    {
        //repetition en y
        for (int j {}; j < number_of_repetition; j++)
        {
            //creation de l'image dans sa zone
            for (int x{0}; x < image.width(); x++)
            {
                for (int y{0}; y < image.height(); y++)
                {

                }
                // image_turned.save("output/turning_90_degrees_left.png");
            }
        }
    }
};

int main()
{
    sil::Image image{"images/logo.png"};
    //keep_green_only
    // keep_green_only(image);
    // image.save("output/keep_green_only.png");

    //swap_canal_red_and_blue
    // swap_canal_red_and_blue(image);
    // image.save("output/swap_canal_red_and_blue.png");

    //black and white
    // black_and_white(image);
    // image.save("output/black_and_white.png");

    //negative
    // negative(image);
    // image.save("output/negative.png");
    
    //gradient
    // sil::Image image_gradient{300/*width*/, 200/*height*/};
    // gradient(image_gradient, 300);
    // image_gradient.save("output/gradient.png");

    //mirror
    // mirrorside(image);
    // image.save("output/mirrorside.png");

    //noise
    // noise(image);
    // image.save("output/noise.png");

    //turning_90_degrees
    //right
    // turning_90_degrees_right(image);
    //left
    // turning_90_degrees_left(image);

    //rgb_split
    // rgb_split(image);
    // image.save("output/rgb_split.png");

    //brightening
    // sil::Image photo{"images/photo.jpg"};
    // brightening(photo);
    // photo.save("output/brightening.png");

    //darkening
    // sil::Image photo{"images/photo.jpg"};
    // darkening(photo);
    // photo.save("output/darkening.png");

    //create_a_circle
    // sil::Image image_circle{500/*width*/, 500/*height*/};
    // create_a_circle(image_circle);
    // image_circle.save("output/create_a_circle.png");

    //create_border_circle
    // sil::Image image_circle{500/*width*/, 500/*height*/};
    // create_border_circle(image_circle);
    // image_circle.save("output/create_border_circle.png");

    //create_an_animation
    // sil::Image image_animation{500/*width*/, 500/*height*/};
    // create_an_animation(image_animation);

    //rosace
    // sil::Image image_rosace{500/*width*/, 500/*height*/};
    // rosace(image_rosace);
    // image_rosace.save("output/rosace.png");

    //mosaique
    // mosaique(image);
    // image.save("output/mosaique.png");
};