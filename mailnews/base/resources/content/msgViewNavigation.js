/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation. Portions created by Netscape are
 * Copyright (C) 1998-1999 Netscape Communications Corporation. All
 * Rights Reserved.
 */

/*  This file contains the js functions necessary to implement view navigation within the 3 pane. */

// These are the types of navigation you can do
var navigateAny=0;
var navigateUnread = 1;
var navigateFlagged = 2;
var navigateNew = 3;


/*GoNextMessage finds the message that matches criteria and selects it.  
  nextFunction is the function that will be used to detertime if a message matches criteria.
  It must take a node and return a boolean.
  nextResourceFunction is the function that will be used to determine if a message in the form of a resource
  matches criteria.  Takes a resource and returns a boolean
  nextThreadFunction is an optional function that can be used to optimize whether or not a thread will have a
  message that matches the criteria.  Takes the top level message in the form of a node and returns a boolean.
  startFromBeginning is a boolean that states whether or not we should start looking at the beginning
  if we reach the end 
*/
function GoNextMessage(type, startFromBeginning )
{
	var beforeGoNextMessage = new Date();

	var tree = GetThreadTree();
	
	var selArray = tree.selectedItems;
	var length = selArray.length;

	if ( selArray && ((length == 0) || (length == 1)) )
	{
		var currentMessage;

		if(length == 0)
			currentMessage = null;
		else
			currentMessage = selArray[0];

		var nextMessage = msgNavigationService.FindNextMessage(type, tree, currentMessage, RDF, document, startFromBeginning, messageView.showThreads);
		//Only change the selection if there's a valid nextMessage
		if(nextMessage && (nextMessage != currentMessage))
			ChangeSelection(tree, nextMessage);
	}

	var afterGoNextMessage = new Date();
	var timeToGetNext = (afterGoNextMessage.getTime() - beforeGoNextMessage.getTime())/1000;
	dump("time to GoNextMessage is " + timeToGetNext + "seconds\n");

}


/*GoPreviousMessage finds the message that matches criteria and selects it.  
  previousFunction is the function that will be used to detertime if a message matches criteria.
  It must take a node and return a boolean.
  startFromEnd is a boolean that states whether or not we should start looking at the end
  if we reach the beginning 
*/
function GoPreviousMessage(type, startFromEnd)
{
	var tree = GetThreadTree();
	
	var selArray = tree.selectedItems;
	if ( selArray && (selArray.length == 1) )
	{
		var currentMessage = selArray[0];
		var previousMessage = msgNavigationService.FindPreviousMessage(type, tree, currentMessage, RDF, document, startFromEnd, messageView.showThreads);
		//Only change selection if there's a valid previous message.
		if(previousMessage && (previousMessage != currentMessage))
			ChangeSelection(tree, previousMessage);
	}
}





// type is the the type of the next thread we are looking for.
// startFromBeginning is true if we should start looking from the beginning after we get to the end of the thread pane.
// gotoNextInThread is true if once we find an unrad thread we should select the first message in that thread that fits criteria
function GoNextThread(type, startFromBeginning, gotoNextInThread)
{

	if(messageView.showThreads)
	{
		var tree = GetThreadTree();
		
		var selArray = tree.selectedItems;
		var length = selArray.length;

		if ( selArray && ((length == 0) || (length == 1)) )
		{
			var currentMessage;

			if(length == 0)
				currentMessage = null;
			else
				currentMessage = selArray[0];

			var nextMessage;
			var currentTopMessage;
			var checkCurrentTopMessage;
			//Need to get the parent message for the current selection to begin to find thread
			if(currentMessage)
			{
				//need to find its top level message and we don't want it to be checked for criteria
				currentTopMessage = FindTopLevelMessage(currentMessage);
				checkCurrentTopMessage = false;
			}
			else
			{
				//currentTopmessage is the first one in the tree and we want it to be checked for criteria.
				currentTopMessage = msgNavigationService.FindFirstMessage(tree);
				checkCurrentTopMessage = true;
			}

			var nextTopMessage = msgNavigationService.FindNextThread(type, tree, currentTopMessage, RDF, document, startFromBeginning, checkCurrentTopMessage);

			var changeSelection = (nextTopMessage != null && ((currentTopMessage != nextTopMessage) || checkCurrentTopMessage));
			if(changeSelection)
			{
				if(gotoNextInThread)
				{
					nextMessage = msgNavigationService.FindNextInThread(type, tree, nextTopMessage, RDF, document);
					ChangeSelection(tree, nextMessage);
				}
				else
					ChangeSelection(tree, nextTopMessage);	
			}
		}
	}

}

function FindTopLevelMessage(startMessage)
{
	var currentTop = startMessage;
	var parent = startMessage.parentNode.parentNode;

	while(parent.localName == 'treeitem')
	{
		currentTop = parent;
		parent = parent.parentNode.parentNode;
	}

	return currentTop;
}


function ScrollToFirstNewMessage()
{
	var tree = GetThreadTree();
	var treeFolder = GetThreadTreeFolder();

	var folderURI = treeFolder.getAttribute('ref');
	var folderResource = RDF.GetResource(folderURI);
	var folder = folderResource.QueryInterface(Components.interfaces.nsIMsgFolder);
	var hasNew = folder.hasNewMessages();
	if(hasNew)
	{
		var newMessage = folder.firstNewMessage;

		if(messageView.showThreads)
		{
			//if we're in thread mode, then we need to actually make sure the message is showing.
			var topLevelMessage = GetTopLevelMessageForMessage(newMessage, folder);
			var topLevelResource = topLevelMessage.QueryInterface(Components.interfaces.nsIRDFResource);
			var topLevelURI = topLevelResource.Value;
			var topElement = document.getElementById(topLevelURI);
			if(topElement)
			{
				msgNavigationService.OpenTreeitemAndDescendants(topElement);
			}

		}
		
		var messageResource = newMessage.QueryInterface(Components.interfaces.nsIRDFResource);
		var messageURI = messageResource.Value;
		var messageElement = document.getElementById(messageURI);

		if(messageElement)
		{
			tree.ensureElementIsVisible(messageElement); 
		}
	}
}

function GetTopLevelMessageForMessage(message, folder)
{
	if(!folder)
		folder = message.msgFolder;

	var thread = folder.getThreadForMessage(message);
    var outIndex = new Object();
	var rootHdr = thread.GetRootHdr(outIndex);

	var topMessage = folder.createMessageFromMsgDBHdr(rootHdr);

	return topMessage;

}


