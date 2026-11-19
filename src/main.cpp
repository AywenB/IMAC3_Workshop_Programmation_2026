#include <sil/sil.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <complex>
#include <cmath>
#include <glm/gtx/matrix_transform_2d.hpp>
// #include <glm>

void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
};

void swap_canal_red_and_blue(sil::Image &image)
{
    float chair{0.f};
    for (glm::vec3 &color : image.pixels())
    {
        chair = color.r;
        color.r = color.b;
        color.b = chair;
        // ou ceci :
        //  std::swap(color.r, color.b);
    }
};

void black_and_white(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float gray_area = (color.b + color.r + color.g) / 3.f;
        color.r = gray_area;
        color.g = gray_area;
        color.b = gray_area;
    }
};

void negative(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.g = 1.f - color.g;
        color.b = 1.f - color.b;
    }
};

void gradient(sil::Image &image, int width)
{
    float const pas = 1.f / width;
    float color_gradient{0.f};
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

void mirrorside(sil::Image &image)
{
    int const width = image.width() - 1;
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y), image.pixel(width - x, y));
        }
    }
};

void noise(sil::Image &image)
{
    float alea_color{0.f};
    int const percentage_of_noise{20};
    for (glm::vec3 &color : image.pixels())
    {
        // generation nombre aléatoire pour si on change le pixel
        int random_number_between_1_and_10_included{std::rand() % 100 + 1};
        if (random_number_between_1_and_10_included <= percentage_of_noise)
        {
            alea_color = (float)rand() / (float)RAND_MAX;
            color.r = alea_color;

            alea_color = (float)rand() / (float)RAND_MAX;
            color.g = alea_color;

            alea_color = (float)rand() / (float)RAND_MAX;
            color.b = alea_color;
        }
    }
};

void turning_90_degrees_right(sil::Image &image)
{
    sil::Image image_turned{image.height() /*width*/, image.width() /*height*/};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).r, image_turned.pixel(y, x).r);
            std::swap(image.pixel(x, y).b, image_turned.pixel(y, x).b);
            std::swap(image.pixel(x, y).g, image_turned.pixel(y, x).g);
        }
        image_turned.save("output/turning_90_degrees_right.png");
    }
};

void turning_90_degrees_left(sil::Image &image)
{
    sil::Image image_turned{image.height() /*width*/, image.width() /*height*/};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).r, image_turned.pixel(image.height() - y - 1, image.width() - x - 1).r);
            std::swap(image.pixel(x, y).b, image_turned.pixel(image.height() - y - 1, image.width() - x - 1).b);
            std::swap(image.pixel(x, y).g, image_turned.pixel(image.height() - y - 1, image.width() - x - 1).g);
        }
        image_turned.save("output/turning_90_degrees_left.png");
    }
};

void rgb_split(sil::Image &image)
{
    // vert ne bouge pas
    // rouge va vers la droite
    // bleu va vers la gauche

    unsigned int const decalage_px{25};

    // bleu
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x - decalage_px < 0)
            {
                image.pixel(x, y).b = 0.f;
            }
            else
            {
                std::swap(image.pixel(x, y).b, image.pixel(x - decalage_px, y).b);
            }
        }
    }

    // rouge
    for (int x{image.width() - 1}; x >= 0; x--)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (x + decalage_px >= image.width())
            {
                image.pixel(x, y).r = 0.f;
            }
            else
            {
                std::swap(image.pixel(x, y).r, image.pixel(x + decalage_px, y).r);
            }
        }
    }
};

void brightening(sil::Image &image)
{
    float const add{0.5f};
    for (glm::vec3 &color : image.pixels())
    {
        color.r = sqrt(color.r);
        color.g = sqrt(color.g);
        color.b = sqrt(color.b);
    }
};

void darkening(sil::Image &image)
{
    float const substract{0.5f};
    for (glm::vec3 &color : image.pixels())
    {
        color.r = pow(color.r, 2);
        color.g = pow(color.g, 2);
        color.b = pow(color.b, 2);
    }
};

void create_a_circle(sil::Image &image)
{
    unsigned int const radius_circle{100};
    int const center_x{image.width() / 2};
    int const center_y{image.height() / 2};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            // si le point est dans le cercle
            if (static_cast<int>(sqrt((pow((x - center_x), 2) + pow((y - center_y), 2)))) < radius_circle)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
};

void create_border_circle(sil::Image &image){
    unsigned int const radius_circle{100};
    unsigned int const thickness{10};
    int const center_x{image.width() / 2};
    int const center_y{image.height() / 2};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int distance_from_the_center = static_cast<int>(sqrt((pow((x - center_x), 2) + pow((y - center_y), 2))));
            // si le point est dans le cercle
            if (distance_from_the_center < radius_circle && distance_from_the_center > radius_circle - thickness)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
};

void create_an_animation(sil::Image &image){
    unsigned int const radius_circle{100};
    int center_x{0};
    int const center_y{image.height() / 2};
    int const number_of_frames{5};
    int const pas{image.width() / number_of_frames};

    for (int i{}; i < number_of_frames; i++)
    {
        // creation du cercle
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                // si le point est dans le cercle
                if (static_cast<int>(sqrt((pow((x - center_x), 2) + pow((y - center_y), 2)))) < radius_circle)
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
        // sauvegarde de la frame
        image.save("output/animation/" + std::to_string(i) + ".png");

        // reinitialisation de l'img
        for (glm::vec3 &color : image.pixels())
        {
            color.r = 0.f;
            color.g = 0.f;
            color.b = 0.f;
        }

        // decalage du cercle
        center_x += pas;
    }
};

void rosace(sil::Image &image){
    unsigned int const radius_circle{100};
    unsigned int const thickness{5};
    double const pas_angle{60 * M_PI / 180};
    int center_x{image.width() / 2};
    int center_y{image.height() / 2};

    // creation du 1er cercle avec bordure
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int distance_from_the_center = static_cast<int>(sqrt((pow((x - center_x), 2) + pow((y - center_y), 2))));
            // si le point est dans le cercle
            if (distance_from_the_center < radius_circle + thickness / 2 && distance_from_the_center > radius_circle - thickness / 2)
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }

    // creation des cercles sur le cercle n°1
    for (double angle{0}; angle < 2 * M_PI; angle += pas_angle)
    {
        // calcul du centre du nouveau cercle
        center_x = static_cast<int>(radius_circle * cos(angle) + image.width() / 2 /*pour recentrer*/);
        center_y = static_cast<int>(radius_circle * sin(angle) + image.height() / 2 /*pour recentrer*/);
        // creation du nouveau cercle en fonction du nouveau centre
        for (int x{0}; x < image.width(); x++)
        {
            for (int y{0}; y < image.height(); y++)
            {
                int distance_from_the_center = static_cast<int>(sqrt((pow((x - center_x), 2) + pow((y - center_y), 2))));
                // si le point est dans le cercle
                if ((distance_from_the_center < radius_circle + thickness / 2) && (distance_from_the_center > radius_circle - thickness / 2))
                {
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
    }
};

void mosaique(sil::Image &image) {
    sil::Image image_mosaique{image.width() /*width*/, image.height() /*height*/};
    int const number_of_repetition{7};
    for (int x{}; x < image_mosaique.width(); x++)
    {
        for (int y{}; y < image_mosaique.height(); y++)
        {
            image_mosaique.pixel(x, y) = image.pixel((x * number_of_repetition) % image.width(), (y * number_of_repetition) % image.height());
        }
    }
    image_mosaique.save("output/mosaique.png");
};

void mosaique_mirroir_reverse_ligne(sil::Image &image)
{
    int const height = image.height() - 1;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height() / 2; y++)
        {
            std::swap(image.pixel(x, y), image.pixel(x, height - y));
        }
    }
}

void mosaique_mirroir(sil::Image &image) {
    sil::Image image_mosaique{image.width() /*width*/, image.height() /*height*/};
    int const number_of_repetition{5};
    int tour{};
    sil::Image image_en_cours{image};
    // creation des deux images à utiliser :
    sil::Image image_reverse{image};
    mirrorside(image_reverse);
    for (int x{}; x < image_mosaique.width(); x++)
    {
        for (int y{}; y < image_mosaique.height(); y++)
        {
            image_mosaique.pixel(x, y) = image_en_cours.pixel((x * number_of_repetition) % image_en_cours.width(), (y * number_of_repetition) % image_en_cours.height());

            // changement de sens de la ligne
            //  std::cout << (y*number_of_repetition)%image_en_cours.height() << std::endl;
            if ((y * number_of_repetition) % image_en_cours.height() == 0 && y > 0)
            {
                mosaique_mirroir_reverse_ligne(image);
                mosaique_mirroir_reverse_ligne(image_reverse);
                image_en_cours = tour % 2 == 0 ? image : image_reverse;
            }
        }
        // changement de sens du logo
        if ((x * number_of_repetition) % image_en_cours.width() == 0 && x > 0)
        {
            tour++;
            image_en_cours = tour % 2 == 0 ? image : image_reverse;
        }
    }
    image_mosaique.save("output/mosaique_mirroir.png");
};

void glitch(sil::Image &image)
{
    int const number_of_boxes{100};
    int const largeur_glitch{10};
    int const hauteur_glitch{50};

    for (int i{}; i < number_of_boxes; i++)
    {
        // coordonnes du glitch
        int height_glitch_random_number{std::rand() % image.height() / hauteur_glitch + 1};
        int width_glitch_random_number{std::rand() % image.width() / largeur_glitch + 1};
        int x_center_glitch_random_number{std::rand() % (image.width() - 1 - width_glitch_random_number) + 1};
        int y_center_glitch_random_number{std::rand() % (image.height() - 1 - height_glitch_random_number) + 1};

        // coordonnees du centre de la boîte de depart
        int x_center_random_number{std::rand() % (image.width() - 1 - width_glitch_random_number) + 1};
        int y_center_random_number{std::rand() % (image.height() - 1 - height_glitch_random_number) + 1};

        for (int x{0}; x < width_glitch_random_number; x++)
        {
            for (int y{0}; y < height_glitch_random_number; y++)
            {
                std::swap(image.pixel(x + x_center_random_number, y + y_center_random_number) /*normal*/, image.pixel(x + x_center_glitch_random_number, y + y_center_glitch_random_number) /*glitch*/);
            }
        }
    }
}

float brightness(glm::vec3 color)
{
    return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

void sorting_all_pixels(sil::Image &image) {
    std::sort(image.pixels().begin(), image.pixels().end(), [](glm::vec3 const &color1, glm::vec3 const &color2)
              { return brightness(color1) < brightness(color2); });
}

void sorting_pixels_line_by_line(sil::Image &image)
{
    for (int ligne{}; ligne < image.height(); ligne++)
    {
        std::sort(image.pixels().begin() + image.width() * ligne, image.pixels().begin() + image.width() + image.width() * ligne, [](glm::vec3 const &color1, glm::vec3 const &color2)
                  { return brightness(color1) < brightness(color2); });
    }
}

void sorting_pixels_randomly(sil::Image &image)
{
    int const number_of_random_lines{50};
    for (int i{}; i < number_of_random_lines; i++)
    {
        int start_line{std::rand() % (image.pixels().size()-1) + 1};
        int end_line{start_line + 60};

        std::sort(image.pixels().begin() + start_line, image.pixels().begin() + end_line, [](glm::vec3 const &color1, glm::vec3 const &color2)
                  { return brightness(color1) < brightness(color2); });
    }
}

void fractale(sil::Image &image)
{
    int const precision {15};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            std::complex<float> c {(static_cast<float>(x-image.width())/2)/100 +1.5, (static_cast<float>(y-image.height())/2)/100 +1}; //TODO mapper pour que ce soit entre -2 et 2
            std::complex<float> z {0,0};
            //verification de la fractal
            float gradient {};
            for (gradient; gradient < precision; gradient++)
            {
                //fractal artistique
                z = sqrt(z)*z+c;
                if(std::abs(z) > 2) {
                    break;
                }

                //fractal normal
                // z = z*z+c;
                // if(std::abs(z) > 2) {
                //     break;
                // }
            }
            gradient /= precision;
            image.pixel(x,y).r = gradient;
            image.pixel(x,y).g = gradient;
            image.pixel(x,y).b = gradient;
        }
    }
}

void gradient_between_two_colors(sil::Image& image, int width, glm::vec3 const color1, glm::vec3 const color2) {
    //v1
    
    // glm::vec3 const pas = {(color2.r - color1.r) / width, (color2.g - color1.g) / width, (color2.b - color1.b) / width};
    // glm::vec3 color_gradient = {color1.r, color1.b, color1.g};
    // for (int x{0}; x < image.width(); x++)
    // {
    //     for (int y{0}; y < image.height(); y++)
    //     {
    //         image.pixel(x, y).r += color_gradient.r;
    //         image.pixel(x, y).g += color_gradient.g;
    //         image.pixel(x, y).b += color_gradient.b;
    //     }
    //     color_gradient += pas;
    // }

    //v2

    for (float x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec3 color_mixed = glm::mix(color1, color2, x/image.width());
            image.pixel(x, y).r = color_mixed.r;
            image.pixel(x,y).g = color_mixed.g;
            image.pixel(x, y).b = color_mixed.b;
        }
    }
}

//gradient avec Oklab
struct Lab {double L; double a; double b;};
// struct RGB {double r; double g; double b;};

Lab linear_srgb_to_oklab(glm::vec3 c)  {
    double l = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
	double m = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
	double s = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;

    double l_ = cbrtf(l);
    double m_ = cbrtf(m);
    double s_ = cbrtf(s);

    return {
        0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
        1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
        0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,
    };
}

glm::vec3 oklab_to_linear_srgb(Lab c) 
{
    double l_ = c.L + 0.3963377774f * c.a + 0.2158037573f * c.b;
    double m_ = c.L - 0.1055613458f * c.a - 0.0638541728f * c.b;
    double s_ = c.L - 0.0894841775f * c.a - 1.2914855480f * c.b;

    double l = l_*l_*l_;
    double m = m_*m_*m_;
    double s = s_*s_*s_;

    return {
		+4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
		-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
		-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

glm::vec3 srgb_to_linear_srgb(glm::vec3 color)  {
    color.r = ( color.r < 0.04045 ) ? color.r * 0.0773993808 : pow( color.r * 0.9478672986 + 0.0521327014, 2.4 );
    color.g = ( color.g < 0.04045 ) ? color.g * 0.0773993808 : pow( color.g * 0.9478672986 + 0.0521327014, 2.4 );
    color.b = ( color.b < 0.04045 ) ? color.b * 0.0773993808 : pow( color.b * 0.9478672986 + 0.0521327014, 2.4 );
    return color;
}

glm::vec3 linear_srgb_to_srgb(glm::vec3 color)  {
    color.r = ( color.r < 0.0031308 ) ? color.r * 12.92 : 1.055 * ( pow( color.r, 0.41666 ) ) - 0.055;
    color.g = ( color.g < 0.0031308 ) ? color.g * 12.92 : 1.055 * ( pow( color.g, 0.41666 ) ) - 0.055;
    color.b = ( color.b < 0.0031308 ) ? color.b * 12.92 : 1.055 * ( pow( color.b, 0.41666 ) ) - 0.055;
    return color;
}

void gradient_oklab_between_two_colors(sil::Image& image, glm::vec3 color1, glm::vec3 color2) {
    glm::vec3 srgb_color_gradient;

    //conversion vers oklab
    Lab color1_lab = linear_srgb_to_oklab(srgb_to_linear_srgb(color1));
    Lab color2_lab = linear_srgb_to_oklab(srgb_to_linear_srgb(color2));
    
    //definition du dégradé
    Lab const pas = {(color2_lab.L - color1_lab.L) / image.width(), (color2_lab.a - color1_lab.a) / image.width(), (color2_lab.b - color1_lab.b) / image.width()};
    Lab color_gradient = {color1_lab.L, color1_lab.a, color1_lab.b};
    
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            //reconversion vers RGB
            srgb_color_gradient = linear_srgb_to_srgb(oklab_to_linear_srgb(color_gradient));

            //mise en place du pixel dans l'image
            image.pixel(x, y).r += srgb_color_gradient.r;
            image.pixel(x, y).g += srgb_color_gradient.g;
            image.pixel(x, y).b += srgb_color_gradient.b;
        }
        color_gradient.a += pas.a;
        color_gradient.b += pas.b;
        color_gradient.L += pas.L;
    }
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void bricbrac(sil::Image& image) {
    for (int x {}; x < image.width(); x++)
    {
        for (int y {}; y < image.height(); y++)
        {
            glm::vec2 pixel_rotated = rotated({x,y}, {image.width()/2, image.height()/2}, 1.25); 
            pixel_rotated.x = pixel_rotated.x < 0 ? 0 : pixel_rotated.x;
            pixel_rotated.x = pixel_rotated.x >= image.width() ? image.width()-1 : pixel_rotated.x;
            pixel_rotated.y = pixel_rotated.y < 0 ? 0 : pixel_rotated.y;
            pixel_rotated.y = pixel_rotated.y >= image.height() ? image.height()-1 : pixel_rotated.y;
            std::swap(image.pixel(x,y), image.pixel(pixel_rotated.x,pixel_rotated.y));
        }
    }
}

float distance_between_two_points(glm::vec2 point1, glm::vec2 point2) {
    return sqrt(pow((point1.x-point2.y), 2)+pow((point1.x-point2.y), 2));
}

void oeil_terrifiant(sil::Image& image) {
    for (int x {}; x < image.width(); x++)
    {
        for (int y {}; y < image.height(); y++)
        {
            //calcul distance entre deux points
            float distance = distance_between_two_points({x,y}, {image.width()/2, image.height()/2});

            //calcule position point qui tourne
            glm::vec2 pixel_rotated = rotated({x,y}, {image.width()/2, image.height()/2}, M_PI*distance); 
            pixel_rotated.x = pixel_rotated.x < 0 ? 0 : pixel_rotated.x;
            pixel_rotated.x = pixel_rotated.x >= image.width() ? image.width()-1 : pixel_rotated.x;
            pixel_rotated.y = pixel_rotated.y < 0 ? 0 : pixel_rotated.y;
            pixel_rotated.y = pixel_rotated.y >= image.height() ? image.height()-1 : pixel_rotated.y;
            std::swap(image.pixel(x,y), image.pixel(pixel_rotated.x,pixel_rotated.y));
        }
    } 
}

void vortex(sil::Image& image) {
    sil::Image image_vortex = {image.width(), image.height()};
    glm::vec2 centre_rotation {image.width()/2, image.height()/2};
    float angle = 4 * M_PI;
    for (int x {}; x < image.width(); x++)
    {
        for (int y {}; y < image.height(); y++)
        {
            //calcul distance entre deux points
            float distance = glm::distance({x, y},centre_rotation);
            float rotation = -angle*(distance/100);
            //calcule position point qui tourne
            glm::vec2 pixel_rotated = rotated({x,y}, {image_vortex.width()/2, image_vortex.height()/2}, rotation);

            if(pixel_rotated.x >= 0 && pixel_rotated.x < image.width() && pixel_rotated.y >= 0 && pixel_rotated.y < image.height()) {
                image_vortex.pixel(x,y) = image.pixel(pixel_rotated.x,pixel_rotated.y);
            }
            // pixel_rotated.x = pixel_rotated.x < 0 ? 0 : pixel_rotated.x;
            // pixel_rotated.x = pixel_rotated.x >= image.width() ? image.width()-1 : pixel_rotated.x;
            // pixel_rotated.y = pixel_rotated.y < 0 ? 0 : pixel_rotated.y;
            // pixel_rotated.y = pixel_rotated.y >= image.height() ? image.height()-1 : pixel_rotated.y;
        }
    }
    image_vortex.save("output/vortex.png");
}

void blur(sil::Image& image) {
    sil::Image finale_image = {image.width(), image.height()};
    int const strength_blur {5};
    int x_coordonnee_finale {};
    int y_coordonnee_finale {};
    //on parcourt l'image
    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            glm::vec3 final_color = {{}, {}, {}};
            //addition de tous les pixels autour du pixel en cours
            for (int x_autour {-strength_blur + x}; x_autour < strength_blur+1+x; x_autour++)
            {
                for (int y_autour {-strength_blur + y}; y_autour < strength_blur+1+y; y_autour++)
                {
                    //verification pour que ça ne sorte pas de l'image
                    if(x_autour < 0) {
                        x_coordonnee_finale = 0;
                    } else if (x_autour >= image.width()){
                        x_coordonnee_finale = image.width()-1;
                    } else {
                        x_coordonnee_finale = x_autour;
                    }
                    if(y_autour < 0) {
                        y_coordonnee_finale = 0;
                    } else if (y_autour >= image.height()){
                        y_coordonnee_finale = image.height()-1;
                    } else {
                        y_coordonnee_finale = y_autour;
                    }

                    final_color.r += image.pixel(x_coordonnee_finale,y_coordonnee_finale).r/pow(2*strength_blur+1, 2);
                    final_color.g += image.pixel(x_coordonnee_finale,y_coordonnee_finale).g/pow(2*strength_blur+1, 2);
                    final_color.b += image.pixel(x_coordonnee_finale,y_coordonnee_finale).b/pow(2*strength_blur+1, 2);
                }
            }
            finale_image.pixel(x,y).r = final_color.r;
            finale_image.pixel(x,y).g = final_color.g;
            finale_image.pixel(x,y).b = final_color.b;
        }
    }

    finale_image.save("output/blur.png");
}

void neon(sil::Image& image) {
    sil::Image finale_image = {image.width(), image.height()};
    int const strength_blur {13};
    int x_coordonnee_finale {};
    int y_coordonnee_finale {};
    int importance_de_la_case {};
    //on parcourt l'image
    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            glm::vec3 final_color = {{}, {}, {}};
            //addition de tous les pixels autour du pixel en cours
            for (int x_autour {-strength_blur}; x_autour < strength_blur+1; x_autour++)
            {
                for (int y_autour {-strength_blur}; y_autour < strength_blur+1; y_autour++)
                {
                    //verification pour que ça ne sorte pas de l'image
                    if(x_autour+x < 0) {
                        x_coordonnee_finale = 0;
                    } else if (x_autour+x >= image.width()){
                        x_coordonnee_finale = image.width()-1;
                    } else {
                        x_coordonnee_finale = x_autour+x;
                    }
                    if(y_autour+y < 0) {
                        y_coordonnee_finale = 0;
                    } else if (y_autour+y >= image.height()){
                        y_coordonnee_finale = image.height()-1;
                    } else {
                        y_coordonnee_finale = y_autour+y;
                    }

                    if(abs(y_autour)+abs(x_autour) == 0) {
                        importance_de_la_case = 1;
                    } else {
                        importance_de_la_case = abs(y_autour)+abs(x_autour)*2;
                    }
                    final_color.r += image.pixel(x_coordonnee_finale,y_coordonnee_finale).r*(0.05/importance_de_la_case);
                    final_color.g += image.pixel(x_coordonnee_finale,y_coordonnee_finale).g*(0.05/importance_de_la_case);
                    final_color.b += image.pixel(x_coordonnee_finale,y_coordonnee_finale).b*(0.05/importance_de_la_case);

                }
            }
            finale_image.pixel(x,y).r = final_color.r;
            finale_image.pixel(x,y).g = final_color.g;
            finale_image.pixel(x,y).b = final_color.b;
        }
    }

    finale_image.save("output/neon.png");
}

void outline(sil::Image& image) {
    sil::Image finale_image = {image.width(), image.height()};
    int const strength_blur {1};
    int x_coordonnee_finale {};
    int y_coordonnee_finale {};
    int importance_de_la_case {};
    //on parcourt l'image
    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            glm::vec3 final_color = {{}, {}, {}};
            //addition de tous les pixels autour du pixel en cours
            for (int x_autour {-strength_blur}; x_autour < strength_blur+1; x_autour++)
            {
                for (int y_autour {-strength_blur}; y_autour < strength_blur+1; y_autour++)
                {
                    //verification pour que ça ne sorte pas de l'image
                    if(x_autour+x < 0) {
                        x_coordonnee_finale = 0;
                    } else if (x_autour+x >= image.width()){
                        x_coordonnee_finale = image.width()-1;
                    } else {
                        x_coordonnee_finale = x_autour+x;
                    }
                    if(y_autour+y < 0) {
                        y_coordonnee_finale = 0;
                    } else if (y_autour+y >= image.height()){
                        y_coordonnee_finale = image.height()-1;
                    } else {
                        y_coordonnee_finale = y_autour+y;
                    }

                    if(abs(y_autour)+abs(x_autour) == 0) {
                        importance_de_la_case = 8;
                    } else {
                        importance_de_la_case = -1;
                    }
                    final_color.r += image.pixel(x_coordonnee_finale,y_coordonnee_finale).r*importance_de_la_case;
                    final_color.g += image.pixel(x_coordonnee_finale,y_coordonnee_finale).g*importance_de_la_case;
                    final_color.b += image.pixel(x_coordonnee_finale,y_coordonnee_finale).b*importance_de_la_case;
                }
            }
            finale_image.pixel(x,y).r = final_color.r;
            finale_image.pixel(x,y).g = final_color.g;
            finale_image.pixel(x,y).b = final_color.b;
        }
    }
    finale_image.save("output/outline.png");
}

void emboss(sil::Image& image) {
    sil::Image finale_image = {image.width(), image.height()};
    int const strength_blur {1};
    int x_coordonnee_finale {};
    int y_coordonnee_finale {};
    int importance_de_la_case {};
    //on parcourt l'image
    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            glm::vec3 final_color = {{}, {}, {}};
            //addition de tous les pixels autour du pixel en cours
            for (int x_autour {-strength_blur}; x_autour < strength_blur+1; x_autour++)
            {
                for (int y_autour {-strength_blur}; y_autour < strength_blur+1; y_autour++)
                {
                    //verification pour que ça ne sorte pas de l'image
                    if(x_autour+x < 0) {
                        x_coordonnee_finale = 0;
                    } else if (x_autour+x >= image.width()){
                        x_coordonnee_finale = image.width()-1;
                    } else {
                        x_coordonnee_finale = x_autour+x;
                    }
                    if(y_autour+y < 0) {
                        y_coordonnee_finale = 0;
                    } else if (y_autour+y >= image.height()){
                        y_coordonnee_finale = image.height()-1;
                    } else {
                        y_coordonnee_finale = y_autour+y;
                    }

                    if(abs(y_autour)+abs(x_autour) == 0) {
                        importance_de_la_case = 1;
                    } else {
                        importance_de_la_case = y_autour+x_autour;
                    }
                    final_color.r += image.pixel(x_coordonnee_finale,y_coordonnee_finale).r*importance_de_la_case;
                    final_color.g += image.pixel(x_coordonnee_finale,y_coordonnee_finale).g*importance_de_la_case;
                    final_color.b += image.pixel(x_coordonnee_finale,y_coordonnee_finale).b*importance_de_la_case;
                }
            }
            finale_image.pixel(x,y).r = final_color.r;
            finale_image.pixel(x,y).g = final_color.g;
            finale_image.pixel(x,y).b = final_color.b;
        }
    }
    finale_image.save("output/embross.png");
};

void sharpen(sil::Image& image) {
    sil::Image finale_image = {image.width(), image.height()};
    int const strength_blur {1};
    int x_coordonnee_finale {};
    int y_coordonnee_finale {};
    int importance_de_la_case {};
    //on parcourt l'image
    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            glm::vec3 final_color = {{}, {}, {}};
            //addition de tous les pixels autour du pixel en cours
            for (int x_autour {-strength_blur}; x_autour < strength_blur+1; x_autour++)
            {
                for (int y_autour {-strength_blur}; y_autour < strength_blur+1; y_autour++)
                {
                    //verification pour que ça ne sorte pas de l'image
                    if(x_autour+x < 0) {
                        x_coordonnee_finale = 0;
                    } else if (x_autour+x >= image.width()){
                        x_coordonnee_finale = image.width()-1;
                    } else {
                        x_coordonnee_finale = x_autour+x;
                    }
                    if(y_autour+y < 0) {
                        y_coordonnee_finale = 0;
                    } else if (y_autour+y >= image.height()){
                        y_coordonnee_finale = image.height()-1;
                    } else {
                        y_coordonnee_finale = y_autour+y;
                    }

                    if(abs(y_autour)+abs(x_autour) == 0) {
                        importance_de_la_case = 5;
                    } else if(abs(y_autour) == 1 && abs(x_autour) == 1){
                        importance_de_la_case = -1;
                    } else {
                        importance_de_la_case = 0;
                    }
                    final_color.r += image.pixel(x_coordonnee_finale,y_coordonnee_finale).r*importance_de_la_case;
                    final_color.g += image.pixel(x_coordonnee_finale,y_coordonnee_finale).g*importance_de_la_case;
                    final_color.b += image.pixel(x_coordonnee_finale,y_coordonnee_finale).b*importance_de_la_case;
                }
            }
            finale_image.pixel(x,y).r = final_color.r;
            finale_image.pixel(x,y).g = final_color.g;
            finale_image.pixel(x,y).b = final_color.b;
        }
    }
    finale_image.save("output/sharpen.png");
};

void diamond_square_1(int const taille_n) {
    //definition taille de la carte
    sil::Image carte {static_cast<int>(pow(2, taille_n))+1, static_cast<int>(pow(2, taille_n))+1};
    std::vector<std::vector<int>> tableau_hauteur{};
    // extrémités : entre 1 et 2 puissance n+1 + entre 2 puissance n-1 et  - (2 puissance n-1)
    // centre : moyenne des 4 extrémités + entre 2 puissance n-1 et  - (2 puissance n-1)
    //diamand : moyenne centre extrémités proches + 
    //pour carrée + petit -> pareille ms valeur alea -4 4 descend à -2 2 (2 puissance n-2)

    //deifnition panel hauteur de la carte 
    int const hauteur_max = pow(2, taille_n+1);

    int hauteur_centre {};
    //mise en place des extrémités sur la carte
    for (int i {}; i < 4; i++)
    {
        int hauteur_random = std::rand() % hauteur_max + 1; //hauteur entre hateur_max et 1
        glm::vec3 couleur_random = {static_cast<float>(hauteur_random)/hauteur_max, static_cast<float>(hauteur_random)/hauteur_max, static_cast<float>(hauteur_random)/hauteur_max};
        switch (i)
        {
        case 0:
            carte.pixel(0,0) = couleur_random;
            break;
        case 1:
            carte.pixel(carte.width()-1,0) = couleur_random;
            break;
        case 2:
            carte.pixel(0,carte.height()-1) = couleur_random;
            break;
        
        default:
            carte.pixel(carte.width()-1, carte.height()-1) = couleur_random;
            break;
        }

        hauteur_centre += hauteur_random;
    }

    int max_variante_hauteur {static_cast<int>(pow(2, taille_n-1))};
    hauteur_centre /= 4;
    hauteur_centre += std::rand()% max_variante_hauteur - max_variante_hauteur;

    //centre de la carte
    carte.pixel(carte.width()/2, carte.height()/2) = {static_cast<float>(hauteur_centre)/hauteur_max, static_cast<float>(hauteur_centre)/hauteur_max, static_cast<float>(hauteur_centre)/hauteur_max};
    
    carte.save("output/diamond_square.png");

    
    //partie diamand
    float variante_de_gris{};
    float variante_aleatoire_couleur {};
    for (int i {}; i < 4; i++)
    {
        variante_aleatoire_couleur = (std::rand()% max_variante_hauteur - max_variante_hauteur)/hauteur_max;
        switch (i)
        {
        case 0:
            variante_de_gris = (carte.pixel(carte.width()/2, carte.height()/2).r/*CENTRE*/+carte.pixel(0,0).r/*HG*/+carte.pixel(0,carte.height()-1).r/*BG*/)/3+variante_aleatoire_couleur;/*GAUCHE */
            /*verif variante de gris*/
            if(variante_de_gris > 1) {
                variante_de_gris = 1;
            } else if(variante_de_gris < 0) {
                variante_de_gris = 0;
            }

            carte.pixel(0,carte.height()/2) = {variante_de_gris, variante_de_gris, variante_de_gris};
            break;
        case 1:
            variante_de_gris = (carte.pixel(carte.width()/2, carte.height()/2).r/*CENTRE*/+carte.pixel(0,0).r/*HG*/+carte.pixel(carte.width()-1,0).r/*HD*/)/3+variante_aleatoire_couleur;/*HAUT*/
            
            /*verif variante de gris*/
            if(variante_de_gris > 1) {
                variante_de_gris = 1;
            } else if(variante_de_gris < 0) {
                variante_de_gris = 0;
            }

            carte.pixel(carte.width()/2,0) = {variante_de_gris, variante_de_gris, variante_de_gris};
            break;
        case 2:
            variante_de_gris = (carte.pixel(carte.width()/2, carte.height()/2).r/*CENTRE*/+carte.pixel(carte.width()-1,0).r/*HD*/+carte.pixel(carte.width()-1,carte.height()-1).r/*BD*/)/3+variante_aleatoire_couleur;/*DROITE*/
            
                        /*verif variante de gris*/
            if(variante_de_gris > 1) {
                variante_de_gris = 1;
            } else if(variante_de_gris < 0) {
                variante_de_gris = 0;
            }
            
            carte.pixel(carte.width()-1,carte.height()/2) = {variante_de_gris, variante_de_gris, variante_de_gris};
            break;
        
        default:
            variante_de_gris = (carte.pixel(carte.width()/2, carte.height()/2).r/*CENTRE*/+carte.pixel(carte.width()-1,carte.height()-1).r/*BD*/+carte.pixel(0,carte.height()-1).r/*BG*/)/3+variante_aleatoire_couleur;/*BAS*/
            
                        /*verif variante de gris*/
            if(variante_de_gris > 1) {
                variante_de_gris = 1;
            } else if(variante_de_gris < 0) {
                variante_de_gris = 0;
            }
            
            carte.pixel(carte.width()/2,carte.height()-1) = {variante_de_gris, variante_de_gris, variante_de_gris};
            break;
        }
    }
    

    // //nombre de fois qu'on va repeter les mêmes operations
    // for (int i = 0; i < carte.width()/3; i++)
    // {
    //     /* code */
    // }
    
    carte.save("output/diamond_square.png");
}

void diamond_square(int const taille_n) {
    //definition taille de la carte
    srand(172);
    //TODO verif que les divisions se font sur des valeurs FLOAT
    sil::Image carte {static_cast<int>(pow(2, taille_n))+1, static_cast<int>(pow(2, taille_n))+1};
    std::vector<std::vector<int>> tableau_hauteur{};
    // extrémités : entre 1 et 2 puissance n+1 + entre 2 puissance n-1 et  - (2 puissance n-1)
    // centre : moyenne des 4 extrémités + entre 2 puissance n-1 et  - (2 puissance n-1)
    //diamand : moyenne centre extrémités proches + 
    //pour carrée + petit -> pareille ms valeur alea -4 4 descend à -2 2 (2 puissance n-2)

    //deifnition panel hauteur de la carte 
    int const hauteur_max = pow(2, taille_n+1);

    //mise en place des extrémités sur la carte
    for (int i {}; i < 4; i++)
    {
        int hauteur_random = std::rand() % hauteur_max + 5; //hauteur entre hauteur_max et 1
        glm::vec3 couleur_random = {static_cast<float>(hauteur_random)/hauteur_max, static_cast<float>(hauteur_random)/hauteur_max, static_cast<float>(hauteur_random)/hauteur_max};
        switch (i)
        {
        case 0:
            carte.pixel(0,0) = couleur_random;
            break;
        case 1:
            carte.pixel(carte.width()-1,0) = couleur_random;
            break;
        case 2:
            carte.pixel(0,carte.height()-1) = couleur_random;
            break;
        
        default:
            carte.pixel(carte.width()-1, carte.height()-1) = couleur_random;
            break;
        }
    }

    
    int max_variante_hauteur {static_cast<int>(pow(2, taille_n-1))};
    //boucle de répetition de plus en plus petit du schema
    for (int i {}; i < (pow(2,taille_n)+1)/3; i++)
    {

        //deplacement dans le carree
        for (int X {}; X < pow(2,i); X++)
        {
            carte.save("output/diamond_square.png");
            for (int Y {}; Y < pow(2,i); Y++)
            {
                //PARTIE CENTRE

                //recherche des points sur les extrémités
                glm::vec2 point_haut_gauche {X*((carte.width()-1)/pow(2,i)),
                                            Y*((carte.height()-1)/pow(2,i))};

                glm::vec2 point_haut_droite {X*((carte.width()-1)/pow(2,i)) + (carte.width()-1)/pow(2,i),
                                            Y*((carte.height()-1)/pow(2,i))};

                glm::vec2 point_bas_gauche {X*((carte.width()-1)/pow(2,i)),
                                            Y*((carte.height()-1)/pow(2,i)) + (carte.height()-1)/pow(2,i)};

                glm::vec2 point_bas_droit {X*((carte.width()-1)/pow(2,i)) + (carte.width()-1)/pow(2,i),
                                            Y*((carte.height()-1)/pow(2,i)) + (carte.height()-1)/pow(2,i)};

                float gray_gradient = (carte.pixel(point_haut_gauche.x, point_haut_gauche.y).r
                                        +carte.pixel(point_haut_droite.x, point_haut_droite.y).r
                                        +carte.pixel(point_bas_gauche.x, point_bas_gauche.y).r
                                        +carte.pixel(point_bas_droit.x, point_bas_droit.y).r)/4;
                //ajout d'une couleur aleatoire
                gray_gradient += static_cast<float>(std::rand()% max_variante_hauteur - max_variante_hauteur)/hauteur_max;
                if(gray_gradient <0) {
                    gray_gradient = 0;
                } else if(gray_gradient > 1) {
                    gray_gradient = 1;
                }
                
                //modification de la couleur sur le pixel central
                // glm::vec2 point_centrale = {/*X*/ X*((carte.width()-1)/pow(2,i)) + (carte.width()-1)/pow(2,i),
                //                             /*Y*/ 0
                // }
                glm::vec2 point_centrale = {(X*((carte.width()-1)/pow(2,i)) + (X+1)*(carte.width()-1)/pow(2,i))/*extremite gauxhe*/
                                            /2, //FIXME le point central fait 2/2 puis 2/4 alors que ca devrait être 2/8
                                            (Y*((carte.height()-1)/pow(2,i)) + (Y+1)*(carte.height()-1)/pow(2,i))
                                            /2};
                std::cout << "point centrale: " << point_centrale.x << "|" << point_centrale.y << std::endl;
                // std::cout << "i: " << i << std::endl;
                // std::cout << "H: " << X*((carte.width()-1)/pow(2,i)) + (carte.width()-1)/pow(2,i) << std::endl;
                // std::cout << "BD: " << (carte.width()-1)/pow(2,i) << std::endl;
                
                carte.pixel(point_centrale.x, point_centrale.y) = {gray_gradient, gray_gradient, gray_gradient};


                /*PARTIE DIAMAND*/
                
                float variante_de_gris{};
                float variante_aleatoire_couleur {};
                //on a le point centrale

                for (int i {}; i < 4; i++)
                {
                    variante_aleatoire_couleur = static_cast<float>(std::rand()% max_variante_hauteur - max_variante_hauteur)/hauteur_max;
                    switch (i)
                    {
                        /*HAUT*/
                    case 0:
                        variante_de_gris = (carte.pixel(point_haut_gauche.x,point_haut_gauche.y).r
                                            +carte.pixel(point_haut_droite.x,point_haut_droite.y).r)
                                            /2+variante_aleatoire_couleur;
                        /*verif variante de gris*/
                        if(variante_de_gris > 1) {
                            variante_de_gris = 1;
                        } else if(variante_de_gris < 0) {
                            variante_de_gris = 0;
                        }

                        carte.pixel((X*((carte.width()-1)/pow(2,i)) + (carte.width()-1)/pow(2,i))/2
                                    ,Y*((carte.height()-1)/pow(2,i)))
                                    = {variante_de_gris, variante_de_gris, variante_de_gris};
                        break;

                        /*DROITE*/
                    case 1:
                        //recherche des points à additionner

                        variante_de_gris = (carte.pixel(point_haut_droite.x,point_haut_droite.y).r
                                            +carte.pixel(point_bas_droit.x, point_bas_droit.y).r)
                                            /2+variante_aleatoire_couleur;
                        
                        /*verif variante de gris*/
                        if(variante_de_gris > 1) {
                            variante_de_gris = 1;
                        } else if(variante_de_gris < 0) {
                            variante_de_gris = 0;
                        }

                        carte.pixel(X*((carte.width()-1)/pow(2,i)) + (carte.width()-1)/pow(2,i)
                                    ,(Y*((carte.height()-1)/pow(2,i)) + (carte.height()-1)/pow(2,i))/2)
                                    = {variante_de_gris, variante_de_gris, variante_de_gris};
                        break;


                        /*BAS*/
                    case 2:
                        variante_de_gris = (carte.pixel(point_bas_droit.x, point_bas_droit.y).r
                                            +carte.pixel(point_bas_gauche.x,point_bas_gauche.y).r)
                                            /2+variante_aleatoire_couleur;
                        
                                    /*verif variante de gris*/
                        if(variante_de_gris > 1) {
                            variante_de_gris = 1;
                        } else if(variante_de_gris < 0) {
                            variante_de_gris = 0;
                        }
                        
                        carte.pixel((X*((carte.width()-1)/pow(2,i)) + (carte.width()-1)/pow(2,i))/2,
                                    Y*((carte.height()-1)/pow(2,i)) + (carte.height()-1)/pow(2,i))
                                    = {variante_de_gris, variante_de_gris, variante_de_gris};
                        break;
                    
                        /*GAUCHE*/
                    default:
                        variante_de_gris = (carte.pixel(point_bas_gauche.x, point_bas_gauche.y).r
                                            +carte.pixel(point_haut_gauche.x,point_haut_gauche.y).r)
                                            /2+variante_aleatoire_couleur;
                        
                                    /*verif variante de gris*/
                        if(variante_de_gris > 1) {
                            variante_de_gris = 1;
                        } else if(variante_de_gris < 0) {
                            variante_de_gris = 0;
                        }
                        
                        carte.pixel(X*((carte.width()-1)/pow(2,i))
                                    ,(Y*((carte.height()-1)/pow(2,i)) + (carte.height()-1)/pow(2,i))/2)
                                    = {variante_de_gris, variante_de_gris, variante_de_gris};
                        break;
                    }
                }
            }
        }

        max_variante_hauteur /=2;
    }
    
    carte.save("output/diamond_square.png");
}

int main()
{
    sil::Image image{"images/logo.png"};
    // keep_green_only
    //  keep_green_only(image);
    //  image.save("output/keep_green_only.png");

    // swap_canal_red_and_blue
    //  swap_canal_red_and_blue(image);
    //  image.save("output/swap_canal_red_and_blue.png");

    // black and white
    //  black_and_white(image);
    //  image.save("output/black_and_white.png");

    // negative
    //  negative(image);
    //  image.save("output/negative.png");

    // gradient
    //  sil::Image image_gradient{300/*width*/, 200/*height*/};
    //  gradient(image_gradient, 300);
    //  image_gradient.save("output/gradient.png");

    // mirror
    //  mirrorside(image);
    //  image.save("output/mirrorside.png");

    // noise
    //  noise(image);
    //  image.save("output/noise.png");

    // turning_90_degrees
    // right
    //  turning_90_degrees_right(image);
    // left
    //  turning_90_degrees_left(image);

    // rgb_split
    //  rgb_split(image);
    //  image.save("output/rgb_split.png");

    // brightening
    //  sil::Image photo{"images/photo.jpg"};
    //  brightening(photo);
    //  photo.save("output/brightening.png");

    // darkening
    //  sil::Image photo{"images/photo.jpg"};
    //  darkening(photo);
    //  photo.save("output/darkening.png");

    // create_a_circle
    //  sil::Image image_circle{500/*width*/, 500/*height*/};
    //  create_a_circle(image_circle);
    //  image_circle.save("output/create_a_circle.png");

    // create_border_circle
    //  sil::Image image_circle{500/*width*/, 500/*height*/};
    //  create_border_circle(image_circle);
    //  image_circle.save("output/create_border_circle.png");

    // create_an_animation
    //  sil::Image image_animation{500/*width*/, 500/*height*/};
    //  create_an_animation(image_animation);

    // rosace
    //  sil::Image image_rosace{500/*width*/, 500/*height*/};
    //  rosace(image_rosace);
    //  image_rosace.save("output/rosace.png");

    // mosaique
    //  mosaique(image);
    //  mosaique_mirroir_reverse_ligne(image);

    // mosaique mirroir
    // mosaique_mirroir(image);

    // glitch
    //  glitch(image);
    //  image.save("output/glitch.png");

    // tri de pixel
    // sorting_all_pixels(image);
    // image.save("output/sorting_all_pixels.png");
    // sorting_pixels_line_by_line(image);
    // image.save("output/sorting_pixels_line_by_line.png");
    // sorting_pixels_randomly(image);
    // image.save("output/sorting_pixels_randomly.png");

    // fractal
    // sil::Image image_fractale{500 /*width*/, 500 /*height*/};
    // fractale(image_fractale);
    // image_fractale.save("output/fractale.png");


    //gradient_between_two_colors
    // sil::Image image_gradient{300/*width*/, 200/*height*/};
    // glm::vec3 color2 = {0.f, 1.f, 0.f};
    // glm::vec3 color1 = {1.f, 0.f, 0.f};
    // gradient_between_two_colors(image_gradient, 300, color1, color2);
    // image_gradient.save("output/gradient_between_two_colors.png");

    //gradient_between_two_colors
    // sil::Image image_gradient{300/*width*/, 200/*height*/};
    // glm::vec3 color2 = {0.f, 1.f, 0.f};
    // glm::vec3 color1 = {1.f, 0.f, 0.f};
    // gradient_oklab_between_two_colors(image_gradient, color1, color2);
    // image_gradient.save("output/gradient_oklab_between_two_colors.png");

    //bricbrac
    // bricbrac(image);
    // image.save("output/bricbrac.png");

    //oeil_terrifiant
    // oeil_terrifiant(image);
    // image.save("output/oeil_terrifiant.png");

    //vortex
    // vortex(image);

    //effet neon
    // neon(image);

    // //emboss
    // emboss(image);

    // //outline
    // outline(image);

    //sharpen
    // sharpen(image);

    //blur
    // blur(image);

    //diamond_square
    // sil::Image image_diamond{300/*width*/, 200/*height*/};
    int const taille_carte {3};
    diamond_square(taille_carte);
    // image_diamond.save("output/diamond_square.png");
};