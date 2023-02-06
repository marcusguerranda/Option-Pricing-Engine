# Option-Pricing-Engine

This project was part of Baruch College/Quantnet's C++ course.

In a few words, this project aims at pricing European and American options, along with their suitable "Greeks" or sensitivities. The bulk of the effort was aimed at the design, and as requested, making the code robust, flexible, and efficient.

We also use finite difference methods, Monte Carlo simulations, and other tools. These are included in my pdf file; however, the code is not provided as some parts are proprietary.

While I have put in quite some time aiming to achieve this, there are many other improvements to be made, and I am aware. For example, it would be better practice to have a base class "Option", from which are derived the different types of options: European, American, Bermudian, etc.

There are as well more advanced design patterns, but these are covered in the second course at Baruch College MFE/Quantnet.
