/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */
#ifndef nsHTMLParts_h___
#define nsHTMLParts_h___

#include "nscore.h"
#include "nsISupports.h"
#include "nsIReflowCommand.h"
class nsIArena;
class nsIAtom;
class nsIContent;
class nsIDocument;
class nsIHTMLContent;
class nsIHTMLContentSink;
class nsITextContent;
class nsIURL;
class nsString;
class nsIWebShell;

// Factory methods for creating html content objects
// XXX argument order is wrong (out parameter should be last)
extern nsresult
NS_NewHTMLAnchorElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLAppletElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLAreaElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLBRElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLBaseElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLBaseFontElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLBodyElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLButtonElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLDListElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLDelElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLDirectoryElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLDivElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLEmbedElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLFontElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLFormElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLFrameElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLFrameSetElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLHRElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLHeadElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLHeadingElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLHtmlElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLIFrameElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLImageElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLInputElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLInsElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLIsIndexElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLLIElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLLabelElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLLayerElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLLegendElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLLinkElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLMapElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLMenuElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLMetaElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLModElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLOListElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLObjectElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLOptGroupElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLOptionElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLParagraphElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLParamElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLPreElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLQuoteElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLScriptElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLSelectElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLSpacerElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLSpanElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLStyleElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTableCaptionElement(nsIHTMLContent** aResult,nsIAtom* aTag);

extern nsresult
NS_NewHTMLTableCellElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTableColElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTableElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTableRowElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTableSectionElement(nsIHTMLContent** aResult,nsIAtom* aTag);

extern nsresult
NS_NewHTMLTbodyElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTextAreaElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTfootElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTheadElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLTitleElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLUListElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewHTMLWBRElement(nsIHTMLContent** aResult, nsIAtom* aTag);

extern nsresult
NS_NewTextNode(nsIHTMLContent** aResult);

extern nsresult
NS_NewCommentNode(nsIHTMLContent** aResult);

/**
 * Create a new content object for the given tag.
 * Returns NS_ERROR_NOT_AVAILABLE for an unknown/unhandled tag.
 * Returns some other error on error.
 * Returns NS_OK on success
 */
extern nsresult
NS_CreateHTMLElement(nsIHTMLContent** aResult,
                     const nsString& aTag);

// Factory methods for creating html layout objects

extern nsresult
NS_NewBodyFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                nsIFrame*& aNewFrame);

extern nsresult
NS_NewBRFrame(nsIContent* aContent, nsIFrame* aParentFrame,
              nsIFrame*& aNewFrame);

extern nsresult
NS_NewCommentFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                   nsIFrame*& aFrameResult);

extern nsresult
NS_NewHRFrame(nsIContent* aContent, nsIFrame* aParentFrame,
              nsIFrame*& aNewFrame);

// <frame> and <iframe> 
extern nsresult NS_NewHTMLFrameOuterFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                                          nsIFrame*& aNewFrame);
// <frameset>
extern nsresult NS_NewHTMLFramesetFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                                        nsIFrame*& aNewFrame);

extern nsresult
NS_NewHTMLFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                nsIFrame*& aNewFrame);

extern nsresult
NS_NewImageFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                 nsIFrame*& aFrameResult);

extern nsresult
NS_NewObjectFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                  nsIFrame*& aFrameResult);

nsresult
NS_NewSpacerFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                  nsIFrame*& aResult);

nsresult
NS_NewTextFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                nsIFrame*& aResult);

nsresult
NS_NewWBRFrame(nsIContent* aContent, nsIFrame* aParentFrame,
               nsIFrame*& aResult);

extern nsresult
NS_NewCSSInlineFrame(nsIFrame**  aInstancePtrResult,
                     nsIContent* aContent,
                     nsIFrame*   aParent);

extern nsresult
NS_NewCSSBlockFrame(nsIFrame**  aInstancePtrResult,
                    nsIContent* aContent,
                    nsIFrame*   aParent);

extern nsresult
NS_NewInputButtonFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                       nsIFrame*& aResult);

extern nsresult
NS_NewInputCheckboxFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                         nsIFrame*& aResult);

extern nsresult
NS_NewInputFileFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                     nsIFrame*& aResult);

extern nsresult
NS_NewInputTextFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                     nsIFrame*& aResult);

extern nsresult
NS_NewInputRadioFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                      nsIFrame*& aResult);

extern nsresult
NS_NewHTMLSelectFrame(nsIContent* aContent, nsIFrame* aParentFrame,
                      nsIFrame*& aResult);

// Everything below this line is obsolete...
//----------------------------------------------------------------------
// XXX naming consistency puhleeze!

// XXX passing aWebShell into this is wrong
extern nsresult NS_NewHTMLContentSink(nsIHTMLContentSink** aInstancePtrResult,
                                      nsIDocument* aDoc,
                                      nsIURL* aURL,
                                      nsIWebShell* aWebShell);


extern nsresult
  NS_NewHTMLBullet(nsIHTMLContent** aInstancePtrResult);

/** Create a new table content object <TABLE> */
extern nsresult
NS_NewTablePart(nsIHTMLContent** aInstancePtrResult,
               nsIAtom* aTag);

/** Create a new table row group object <THEAD> <TBODY> <TFOOT> */
extern nsresult
NS_NewTableRowGroupPart(nsIHTMLContent** aInstancePtrResult,
                        nsIAtom* aTag);

/** Create a new table row content object <TR> */
extern nsresult
NS_NewTableRowPart(nsIHTMLContent** aInstancePtrResult,
               nsIAtom* aTag);

/** Create a new table column group content object <COLGROUP> */
extern nsresult
NS_NewTableColGroupPart(nsIHTMLContent** aInstancePtrResult,
                        nsIAtom* aTag);

/** Create a new table column content object <COL> */
extern nsresult
NS_NewTableColPart(nsIHTMLContent** aInstancePtrResult,
                   nsIAtom* aTag); 

/** Create a new table cell content object <TD> */
extern nsresult
NS_NewTableCellPart(nsIHTMLContent** aInstancePtrResult,
                    nsIAtom* aTag);

/** Create a new table caption content object <CAPTION> */
extern nsresult
NS_NewTableCaptionPart(nsIHTMLContent** aInstancePtrResult,
                       nsIAtom* aTag);

extern nsresult
NS_NewHTMLEmbed(nsIHTMLContent** aInstancePtrResult,
                nsIAtom* aTag);

extern nsresult
NS_NewHTMLObject(nsIHTMLContent** aInstancePtrResult,
                 nsIAtom* aTag);

extern nsresult
NS_NewHTMLImage(nsIHTMLContent** aInstancePtrResult,
                nsIAtom* aTag);

extern nsresult
NS_NewHTMLLayer(nsIHTMLContent** aInstancePtrResult,
                nsIAtom* aTag);

/** Create a new HTML reflow command */
extern nsresult
NS_NewHTMLReflowCommand(nsIReflowCommand**           aInstancePtrResult,
                        nsIFrame*                    aTargetFrame,
                        nsIReflowCommand::ReflowType aReflowType,
                        nsIFrame*                    aChildFrame = nsnull);

#endif /* nsHTMLParts_h___ */
