#ifndef EDITOR_SCENE_PAGE_INCLUDED
#define EDITOR_SCENE_PAGE_INCLUDED


#include "minorGems/ui/event/ActionListener.h"

#include "minorGems/io/file/File.h"


#include "GamePage.h"

#include "Picker.h"
#include "TextButton.h"
#include "ValueSlider.h"

#include "objectBank.h"
#include "animationBank.h"

#include "keyLegend.h"

#include "RadioButtonSet.h"



typedef struct SceneCell {
        int biome;
        
        int oID;

        int heldID;
        
        SimpleVector<int> contained;
        SimpleVector< SimpleVector<int> > subContained;

        ClothingSet clothing;

        char flipH;
        double age;
        
        AnimType anim;
        
        // negative to unfreeze time for cell, or positive to freeze
        // time at a given point
        double frozenAnimTime;
        
        // for vanishing/appearing sprites based on use
        int numUsesRemaining;
        
        int xOffset;
        int yOffset;
        
        // for moving cell, where they should end up
        int destCellXOffset;
        int destCellYOffset;

        // for live display only (not saved)
        double moveFractionDone;

        // current move offset in pixels
        doublePair moveOffset;
        
        double moveDelayTime;
        
        double moveStartTime;

    } SceneCell;


    

class EditorScenePage : public GamePage, public ActionListener {
        
    public:
        EditorScenePage();
        ~EditorScenePage();
    
        virtual void actionPerformed( GUIComponent *inTarget );


        virtual void drawUnderComponents( doublePair inViewCenter, 
                                          double inViewSize );
        
        virtual void makeActive( char inFresh );
        
        virtual void keyDown( unsigned char inASCII );
        virtual void keyUp( unsigned char inASCII );
        virtual void specialKeyDown( int inKeyCode );
        
        
    protected:
        
        TextButton mAnimEditorButton;
        
        TextButton mSaveNewButton;
        TextButton mReplaceButton;
        TextButton mDeleteButton;
        
        TextButton mNextSceneButton;
        TextButton mPrevSceneButton;


        TextButton mClearSceneButton;

        Picker mGroundPicker;
        Picker mObjectPicker;
        
        ValueSlider mPersonAgeSlider;
        
        RadioButtonSet mCellAnimRadioButtons;
        RadioButtonSet mPersonAnimRadioButtons;
        
        ValueSlider mCellAnimFreezeSlider;
        ValueSlider mPersonAnimFreezeSlider;
        
        ValueSlider mCellSpriteVanishSlider;

        ValueSlider mCellXOffsetSlider;
        ValueSlider mCellYOffsetSlider;

        ValueSlider mPersonXOffsetSlider;
        ValueSlider mPersonYOffsetSlider;
        
        TextField mCellMoveDelayField;
        TextField mPersonMoveDelayField;
        

        
        SpriteHandle mCellDestSprite;
        SpriteHandle mPersonDestSprite;

        SpriteHandle mGroundOverlaySprite[4];
        
        char mShowUI;
        float mCursorFade;
        
        int mSceneW, mSceneH;
        
        int mSceneID;

        SceneCell **mCells;
        SceneCell **mPersonCells;
        
        SceneCell mEmptyCell;
        SceneCell mCopyBuffer;
        
        
        // when we get near edge of screen with cell selection, we
        // shift everything into the center
        int mShiftX, mShiftY;
        
        int mCurX, mCurY;
        
        double mFrameCount;
        
        char mLittleDheld;
        char mBigDheld;

        File mScenesFolder;
        File *mNextFile;
        int mNextSceneNumber;
        

        KeyLegend mKeyLegend, mKeyLegendG, mKeyLegendC, mKeyLegendP;


        void floodFill( int inX, int inY, int inOldBiome, int inNewBiome );
        

        void drawGroundOverlaySprites();
        
        // check which GUI components should be visible
        void checkVisible();

        SceneCell *getCurrentCell();
        SceneCell *getCurrentPersonCell();
        
        // clear everything but biome
        void clearCell( SceneCell *inCell );
        
        void clearScene();
        

        void restartAllMoves();
        

        File *getSceneFile( int inSceneID );
        
        char tryLoadScene( int inSceneID );
        
        void writeSceneToFile( int inIDToUse );
        
        void checkNextPrevVisible();
        
        void resizeGrid( int inNewH, int inNewW );

    };

        


#endif
