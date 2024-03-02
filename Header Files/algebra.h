#ifndef ALGEBRA_H
#define ALGEBRA_H

// ** INCLUDE GMP LIB FOR BETTER EXPERIENCE
#include <iostream>
#include <gmp.h>
#include <gmpxx.h>
#include <ownerr.h>

/* BASIC ADD ALGEBRA */
mpz_class add(mpz_class num1, mpz_class num2)
{
    try
    { // ** ADD TWO MPZ NUMBER
        mpz_class result;
        mpz_add(result.get_mpz_t(), num1.get_mpz_t(), num2.get_mpz_t());
        return result;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

/* BASIC SUBTRACT ALGEBRA */
mpz_class subtract(mpz_class num1, mpz_class num2)
{
    try
    { // ** SUBTRACT TWO MPZ NUMBER
        mpz_class result{};
        mpz_sub(result.get_mpz_t(), num1.get_mpz_t(), num2.get_mpz_t());
        return result;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

/* BASIC MULTIPLICATION ALGEBRA */
mpz_class multiply(mpz_class num1, mpz_class num2)
{
    try
    { // ** MULTIPLY TWO MPZ NUMBER
        mpz_class result{};
        mpz_mul(result.get_mpz_t(), num1.get_mpz_t(), num2.get_mpz_t());
        return result;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

/* BASIC DVIDE ALGEBRA */
mpz_class dvide(mpz_class num1, mpz_class num2)
{
    try
    { // ** DVIDE TWO MPZ NUMBER
        mpz_class result{};
        mpz_div(result.get_mpz_t(), num1.get_mpz_t(), num2.get_mpz_t());
        return result;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

/* US ALMA ISLEMI */
mpz_class exponentiate(mpz_class base, mpz_class exponent)
{
    try
    {
        // Üs alma işlemini gerçekleştir
        mpz_class result{};
        mpz_pow_ui(result.get_mpz_t(), base.get_mpz_t(), mpz_get_ui(exponent.get_mpz_t()));
        return result;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

/* BASIC MOD ALGEBRA */
mpz_class modulus_ui(mpz_class num1, unsigned long int num2)
{
    try
    { // ** A MPZ NUMBER MODULUS FOR UNSIGNED LONG INT
        mpz_class result{};
        mpz_mod_ui(result.get_mpz_t(), num1.get_mpz_t(), num2);
        return result;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

/* EXTREM MOD ALGEBRA */
mpz_class modulus(mpz_class num1, mpz_class num2)
{
    try
    { // ** TWO MPZ NUMBER MODULUS
        mpz_class result{};
        mpz_mod(result.get_mpz_t(), num1.get_mpz_t(), num2.get_mpz_t());
        return result;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

/* SECURITY FOR X BIT RANDOM TOKENS */
mpz_class generate_random_xbit_number(short int _bit_ = 64)
{
    try
    { // ** CREATE _bit_ Random Number
        /* START RAND. GEN. */
        gmp_randstate_t rand_state;
        gmp_randinit_default(rand_state);

        /* CREATE _bit_BIT RAND. NUM */
        mpz_class iSecure;
        mpz_urandomb(iSecure.get_mpz_t(), rand_state, _bit_);

        /* CLEAN RAND GENERATOR */
        gmp_randclear(rand_state);

        /* LOG */
        std::clog << "Rand iS Done: " << iSecure << std::endl;

        /* RETURN THE RANDOM _bit_BIT iSecure */
        return iSecure;
    }
    catch (std::exception &ex)
    {
        OwnErr();
        return mpz_class();
    }
}

#endif // ALGEBRA_H
