#pragma once
#include "src/MathsOperations.h"

struct TransformationDetails
    {
    unsigned int* trsid;
    vec2* pos;
    vec2* scale;
    unsigned int size;
    int width;
    int height;
    };
typedef struct TransformationDetails TransformationDetails;

/**
 * Initialises the transformation details to enable adding and removing easily
 * 
 * @param width A pointer to the width of the window
 * @param height A pointer to the height of the window
 * 
 * @returns Newly initialised TransformationDetails object
 */
TransformationDetails InitialiseTransformationDetails(unsigned int width, unsigned int height);

/**
 * Returns the index of the transformation
 * 
 * @param tds The details about the transformation
 * @param trsid The ID of the transformation to find
 * 
 * @returns Index of ID in the details object or -1 if not found
 */
int getTransformationIDIndex(TransformationDetails tds, unsigned int trsid);

/**
 * Adds a transformation to the details
 * 
 * @param tds A pointer to the details
 * @param pos The new position to add
 * @param scale The new scale to add
 * 
 * @returns The ID of the newly added transformation
 */
unsigned int AddTransformation(TransformationDetails* tds, vec2 pos, vec2 scale);

/**
 * Removes a transformation from the details
 * 
 * @param tds A pointer to the details
 * @param tid The ID of the object to remove
 */
void RemoveTransformation(TransformationDetails* tds, unsigned int tid);

#pragma region Functions

/**
 * Sets the position of the transform
 * 
 * @param tds The details about the transformation
 * @param trsid The transformation ID
 * @param newpos The new position to apply
 */
void setPosition(TransformationDetails tds, unsigned int trsid, vec2 newpos);

/**
 * Gets the position of the transform
 * 
 * @param tds The details about the transformation
 * @param trsid The transformation ID
 */
vec2 getPosition(TransformationDetails tds, unsigned int trsid);

/**
 * Sets the scale of the transform
 * 
 * @param tds The details about the transformation
 * @param trsid The transformation ID
 * @param newscale The new scale to apply
 */
void setScale(TransformationDetails tds, unsigned int trsid, vec2 newscale);

/**
 * Gets the scale of the transform
 * 
 * @param tds The details about the transformation
 * @param trsid The transformation ID
 */
vec2 getScale(TransformationDetails tds, unsigned int trsid);

/**
 * Gets the model matrix for the transformation
 * 
 * @param tds The details of the transformation object
 * @param tid The ID of the transform record
 * 
 * @returns The model matrix for the relevant transform
 */
m4 getTransformModelMatrix(TransformationDetails tds, unsigned int tid);

/**
 * Gets all of the transformation matrices
 * 
 * @param tds The transformation details
 * @param models An array of m4 matrices (this array will be the size of tds.size)
 */
void getTransformModelMatrices(TransformationDetails tds, m4* models);

/**
 * Gets the projection matrix to be used
 * 
 * @param tds The transformation details
 * 
 * @returns A 4x4 matrix with the projection
 */
m4 getTransformProjectionMatrix(TransformationDetails tds);

#pragma endregion
